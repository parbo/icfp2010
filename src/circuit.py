import re 
import sys
from optparse import OptionParser
import itertools

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

def getixconn(s):
    conn = s[-1:]
    try: 
        ix = int(s[:-1])
    except ValueError:
        ix = None
    return ix, conn

def required(inp, outp):
    return [reqtable[i] for i in zip(inp, outp)]       

def chain(length):
    ret = ["0L:"]
    for i in range(length):
        if i == 0:
            inp = "X%dR"%(length-1)
        else:
            inp = "%dL%dR"%(i-1, i-1)
        
        if i == length - 1:
            outp = "X0R"
        else:
            outp = "%dL%dR"%(i+1, i+1)

        ret.append(inp + "0#" + outp)
    ret.append("%dL"%(length-1,))
    return "\n".join(ret)

def chain_2(length):
    ret = ["0L:"]
    for i in range(length):
        if i == 0:
            inp = "X0R"
        else:
            inp = "%dL%dR"%(i-1, i)
        
        if i == length - 1:
            outp = "X0R"
        else:
            outp = "%dL%dR"%(i+1, i)

        ret.append(inp + "0#" + outp)
    ret.append("%dL"%(length-1,))
    return "\n".join(ret)

def chain_3(length):
    ret = ["0L:"]
    for i in range(length):
        if i == 0:
            inp = "X0L"
        else:
            inp = "%dR%dL"%(i-1, i)
        
        if i == length - 1:
            outp = "0RX"
        else:
            outp = "%dR%dL"%(i, i+1)

        ret.append(inp + "0#" + outp)
    ret.append("%dR"%(length-1,))
    return "\n".join(ret)

def generate_circuit(numnodes, indata=None, outdata=None):
    inputs = [(None, "X")]
    inputs.extend([(i, "L") for i in range(numnodes)])
    inputs.extend([(i, "R") for i in range(numnodes)])
    outputs = [(i, "L") for i in range(numnodes)]
    outputs.extend([(i, "R") for i in range(numnodes)])
    outputs.append((None, "X"))
    permutations = itertools.permutations(outputs)       
    num = 0
    gates = [Gate("", "", "", "") for i in range(numnodes)]
    for p in permutations:
        extin = None
        extout = None
        ok = True
        for o, i in zip(p, inputs):
            outix, outconn = o
            inix, inconn = i
            if outix == None and inix == None:
                ok = False
                break
            
            # Connect g[outix][outconn] -> g[inix][inconn]
            if outix != None:
                g = gates[outix]
                if outconn == "L":
#                    print "set left out on", outix, inix, inconn
                    g.leftoutix = inix
                    g.leftoutconn = inconn
                elif outconn == "R":
#                    print "set right out on ", outix, inix, inconn
                    g.rightoutix = inix
                    g.rightoutconn = inconn
            if inix != None:
                g = gates[inix]
                # reset value of the gate
                g.L = 0
                g.R = 0
                if inconn == "L":
#                    print "set left in on ", inix, outix, outconn
                    g.leftinix = outix
                    g.leftinconn = outconn
                elif inconn == "R":
#                    print "set right in on ", inix, outix, outconn
                    g.rightinix = outix
                    g.rightinconn = outconn

            # Connect X -> g[inix][inconn]
            if outix == None:
                extin = (inix, inconn)                      

            # Connect g[outix][outconn] -> X
            if inix == None:
                extout = (outix, outconn)
            
        if ok and indata != None:
            # print "%s:"%extin
            # gs = [str(g) for g in gates]
            # s= ",\n".join(gs) + ":"
            # print s
            # print extout
            # print

            num += 1
            if (num % 10000) == 0:
                print num
            out = calculate(gates, extin, extout, indata, False, outdata)
            if out == outdata:
                print
                print "Solution for:"
                print indata
                print outdata
                print
                print "%d%s:"%extin
                gs = [str(g) for g in gates]
                s= ",\n".join(gs) + ":"
                print s
                print "%d%s"%extout
                print
                return True
    return False

def check_block(inp, outp, level):    
    if level > 20:
#        print "Bail!"
        return False, level
    if inp == outp:
#        print "OK!"
        return True, level
    else:
#        print "Nope..."
        rightinp, rightoutp = zip(*required(inp, outp))
        ok, finlevel = check_block([0] + list(rightoutp[:-1]), rightinp, level + 1)
        if ok:
            return True, finlevel
        rightinp, rightoutp = zip(*required(inp, outp))
        ok, finlevel = check_block(rightinp, [0] + list(rightoutp[:-1]), level + 1)
        if ok:
            return True, finlevel
        rightinp, rightoutp = zip(*required(outp, inp))
        ok, finlevel = check_block([0] + list(rightoutp[:-1]), rightinp, level + 1)
        if ok:
            return True, finlevel
        rightinp, rightoutp = zip(*required(outp, inp))
        ok, finlevel = check_block(rightinp, [0] + list(rightoutp[:-1]), level + 1)
        if ok:
            return True, finlevel
        return False, level

class InvalidConnector(Exception):
    pass

class Gate(object):
    def __init__(self, iL, iR, oL, oR):
        self.leftinix, self.leftinconn = getixconn(iL)
        self.rightinix, self.rightinconn = getixconn(iR)
        self.leftoutix, self.leftoutconn = getixconn(oL)
        self.rightoutix, self.rightoutconn = getixconn(oR)
        self.L = 0
        self.R = 0

    def calc(self, left, right):
        self.L, self.R = gatetable[(left, right)]

    def __str__(self):
        leftinp = "X"
        if self.leftinix != None:
            leftinp = "%d%s"%(self.leftinix, self.leftinconn)
        rightinp = "X"
        if self.rightinix != None:
            rightinp = "%d%s"%(self.rightinix, self.rightinconn)
        leftoutp = "X"
        if self.leftoutix != None:
            leftoutp = "%d%s"%(self.leftoutix, self.leftoutconn)
        rightoutp = "X"
        if self.rightoutix != None:
            rightoutp = "%d%s"%(self.rightoutix, self.rightoutconn)
        return leftinp + rightinp + "0#" + leftoutp + rightoutp
        # return "'%s' '%s' '%s' '%s' '%s' '%s' '%s' '%s'"%(str(self.leftinix), str(self.leftinconn),
        #                                                   str(self.rightinix), str(self.rightinconn),
        #                                                   str(self.leftoutix), str(self.leftoutconn),
        #                                                   str(self.rightoutix), str(self.rightoutconn
                                                                                    # ))

def calculate(gates, extin, extout, inp, step, wanted=[]):
    outp = []
    outix, extconn = extout
    for s, inval in enumerate(inp):
        if step:
            print "Step:", s
            print "In:", inval
        for i, g in enumerate(gates):
            try:
                lval = getattr(gates[g.leftinix], g.leftinconn)
            except TypeError:
                lval = inval
            try:
                rval = getattr(gates[g.rightinix], g.rightinconn)
            except TypeError:
                rval = inval
            g.calc(lval, rval)
            if step:
                print "Node %2d"%i, g.left, g.right
        val = getattr(gates[outix], extconn)
        try:
            if val != wanted[s]:
                return
        except IndexError:
            pass
        outp.append(val)
        if step:
            print "Out:", outp[-1]
            print
        if step:
            raw_input("Enter to step..")
    return outp

def spec_to_gates(spec):
    connector = r"(X|\d+[R|L])"
    gatetype = r"\d+#"
    re_gate = re.compile(connector + connector + gatetype + connector + connector)
    re_external_input = re.compile(connector + r":")
    re_external_output = re.compile(connector + r"$")
    gates = []
    for line in spec.split():
        m = re_gate.match(line)
        if m:
            gates.append(Gate(m.group(1), m.group(2), m.group(3), m.group(4)))
        m = re_external_input.match(line)
        if m:
            extin = m.group(1)
        m = re_external_output.match(line)
        if m:
            extout = m.group(1)
    return gates, (int(extin[:-1]), extin[-1:]), (int(extout[:-1]), extout[-1:])

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
            r.append("  node_%d:BR:s -> node_%d:T%s:n;"%(i, g.rightoutix, g.rightoutconn))
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

def main():
    parser = OptionParser()
    parser.add_option("-c", "--circuit", dest="circuit",
                      help="Read circuit from FILE", metavar="FILE")
    parser.add_option("-d", "--dot", dest="dotfile",
                      help="Create dot-file FILE", metavar="FILE")
    parser.add_option("-f", "--find", dest="find", action="store_true", default=False,
                  help="Find solution")
    parser.add_option("-i", "--input", dest="inputdata",
                      help="Input data")
    parser.add_option("-o", "--output", dest="outputdata",
                      help="Output data")
    parser.add_option("-s", "--step", dest="step", action="store_true", default=False,
                      help="Step")
    parser.add_option("-g", "--gen", dest="gen", action="store", type="int", default=0,
                      help="Generate circuit")
    (options, args) = parser.parse_args()    

    if options.circuit:
        c = open(options.circuit).read()
        gates, extin, extout = spec_to_gates(c)
        print calculate(gates, extin, extout, eval(options.inputdata), options.step)

    # if options.genchain:
    #     cache = set()
    #     for i in range(1,options.genchain):
    #         gates, extin, extout = spec_to_gates(chain_3(i))
    #         ret = tuple(calculate(gates, extin, extout, eval(options.inputdata), options.step))
    #         if options.outputdata:
    #             if ret == tuple(options.outputdata):
    #                 print "Success!"
    #                 sys.exit(0)
    #         if ret not in cache:
    #             print i, ret
    #             cache.add(ret)

    if options.gen:        
        for i in range(options.gen, 1000):
            print "trying", i
            res = generate_circuit(i, eval(options.inputdata), eval(options.outputdata))
            if res:
                break
            

    # print zip(*required(eval(options.inputdata),
    #                     eval(options.outputdata)))

    if options.dotfile:
        s = gates_to_dot(gates)
        f = open(options.dotfile, "w")
        f.write(s)
        f.close()

    if options.find:
        res, level = check_block(eval(options.inputdata),
                                 eval(options.outputdata),
                                 0)
        print res, level

if __name__=="__main__":
    main()
