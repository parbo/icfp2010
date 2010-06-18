import re 
import sys

def gate(L, R):    
    return gatetable((L, R))

class InvalidConnector(Exception):
    pass

class Gate(object):
    gatetable={(0,0): (0,2),
               (0,1): (2,2),
               (0,2): (1,2),
               (1,0): (1,2),
               (1,1): (0,0),
               (1,2): (2,1),
               (2,0): (2,2),
               (2,1): (1,1),
               (2,2): (0,0)}

    def __init__(self, iL, iR):
        self.leftix = None
        self.leftconn = iL[-1:]
        try: 
            self.leftix = int(iL[:-1])
        except ValueError:
            pass
        self.rightix = None
        self.rightconn = iR[-1:]
        try: 
            self.rightix = int(iR[:-1])
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
        self.left, self.right = self.gatetable[(left, right)]

def calculate(gates, extin, extout, inp):
    outp = []
    outix = int(extout[:-1])
    extconn = extout[-1:]
    for inval in inp:
        for i, g in enumerate(gates):
            try:
#                print g.leftix, g.leftconn
                lval = gates[g.leftix].getval(g.leftconn)
            except TypeError:
                lval = inval
            except InvalidConnector:
                print g.leftix, g.leftconn
                raise
            try:
#                print g.rightix, g.rightconn
                rval = gates[g.rightix].getval(g.rightconn)
            except TypeError:
                rval = inval
            except InvalidConnector:
                print g.rightix, g.rightconn
                raise
            g.calc(lval, rval)
        outp.append(gates[outix].getval(extconn))
    return outp

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
            gates.append(Gate(m.group(1), m.group(2)))
        m = re_external_input.match(line)
        if m:
            extin = m.group(1)
        m = re_external_output.match(line)
        if m:
            extout = m.group(1)

    res = calculate(gates, extin, extout, inp)
    print res

if __name__=="__main__":
    main(sys.argv[1], eval(sys.argv[2]))
