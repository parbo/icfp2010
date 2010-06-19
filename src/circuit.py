import re 
import sys

gatetable={(0,0): (0,2),
           (0,1): (2,2),
           (0,2): (1,2),
           (1,0): (1,2),
           (1,1): (0,0),
           (1,2): (2,1),
           (2,0): (2,2),
           (2,1): (1,1),
           (2,2): (0,0)}

reqtable = dict(zip(gatetable.keys(), gatetable.values()))

def required(inp, outp):
    return [reqtable[i] for i in zip(inp, outp)]       

def check_block(inp, outp, level):    
    if level > 100:
        print "Bail!"
        return False, level
    if inp == outp:
        print "OK!"
        return True, level
    else:
        print "Nope..."
        rightinp, rightoutp = zip(*required(inp, outp))
        ok, finlevel = check_block([0] + list(rightoutp[:-1]), rightinp, level + 1)
        if ok:
            return finlevel
        rightinp, rightoutp = zip(*required(inp, outp))
        ok, finlevel = check_block(rightinp, [0] + list(rightoutp[:-1]), level + 1)
        if ok:
            return finlevel

inp, outp = zip(*[(0,1),
                  (1,1),
                  (2,0),
                  (0,2),
                  (2,1),
                  (1,2),
                  (0,1),
                  (1,0),
                  (2,1),
                  (1,1),
                  (0,2),
                  (2,1),
                  (0,0),
                  (1,1),
                  (2,2), 
                  (0,2),
                  (2,1)])

#print check_block(inp, outp, 0)

class InvalidConnector(Exception):
    pass

class Gate(object):
    def __init__(self, iL, iR, oL, oR):
        self.leftinix = None
        self.leftinconn = iL[-1:]
        try: 
            self.leftinix = int(iL[:-1])
        except ValueError:
            pass
        self.rightinix = None
        self.rightinconn = iR[-1:]
        try: 
            self.rightinix = int(iR[:-1])
        except ValueError:
            pass
        self.leftoutix = None
        self.leftoutconn = oL[-1:]
        try: 
            self.leftoutix = int(oL[:-1])
        except ValueError:
            pass
        self.rightoutix = None
        self.rightoutconn = oR[-1:]
        try: 
            self.rightoutix = int(oR[:-1])
        except ValueError:
            pass
        self.left = 0
        self.right = 0

    def getval(self, conn):
        if conn == "L":
            return self.left
        elif conn == "R":
            return self.right
        else:
            raise InvalidConnector        

    def calc(self, left, right):
        self.left, self.right = gatetable[(left, right)]

def calculate(gates, extin, extout, inp):
    outp = []
    outix = int(extout[:-1])
    extconn = extout[-1:]
    for inval in inp:
        for i, g in enumerate(gates):
            try:
                lval = gates[g.leftinix].getval(g.leftinconn)
            except TypeError:
                lval = inval
            except InvalidConnector:
                print g.leftinix, g.leftinconn
                raise
            try:
                rval = gates[g.rightinix].getval(g.rightinconn)
            except TypeError:
                rval = inval
            g.calc(lval, rval)
        outp.append(gates[outix].getval(extconn))
    return outp

def gates_to_dot(gates):
    r = ["digraph structs {"]
#    r.append("  graph [ordering=in];")
    r.append("  node [shape=record];")
    r.append("  node_ext_in [label=\"<in> in\"];")
    r.append("  node_ext_out [label=\"<out> out\"];")
    for i, g in enumerate(gates):
        r.append("  node_%d [label=\"{{<TL>|<TR>}|%d|{<BL>|<BR>}}\"];"%(i, i))
    for i, g in enumerate(gates):        
        try:
            r.append("  node_%d:BL:s -> node_%d:T%s:n;"%(i, g.leftoutix, g.leftoutconn))
        except TypeError:
            r.append("  node_%d:BL:s -> node_ext_in:in:n;"%(i,))
        try:
            r.append("  node_%d:BR:s -> node_%d:T%s:n [weight=%f];"%(i, g.rightoutix, g.rightoutconn))
        except TypeError:
            r.append("  node_%d:BR:s -> node_ext_in:in:n;"%(i,))
        if g.leftinix == None:
            r.append("  node_ext_out:out:s -> node_%d:TL:n;"%(i,))
        if g.rightinix == None:
            r.append("  node_ext_out:out:s -> node_%d:TR:n;"%(i,))            
    for i, g in enumerate(gates):
        r.append("  subgraph g_%d { node_%d; }"%(i, i))
    r.append("}")
    return "\n".join(r)

def main(filename, inp):
    c = open(filename).readlines()
    connector = r"(X|\d+[R|L])"
    gatetype = r"\d+#"
    re_gate = re.compile(connector + connector + gatetype + connector + connector)
    re_external_input = re.compile(connector + r":")
    re_external_output = re.compile(connector + r"$")
    gates = []
    for line in c:
        m = re_gate.match(line)
        if m:
            gates.append(Gate(m.group(1), m.group(2), m.group(3), m.group(4)))
        m = re_external_input.match(line)
        if m:
            extin = m.group(1)
        m = re_external_output.match(line)
        if m:
            extout = m.group(1)

    print gates_to_dot(gates)
    res = calculate(gates, extin, extout, inp)
#    print res

if __name__=="__main__":
    main(sys.argv[1], eval(sys.argv[2]))
