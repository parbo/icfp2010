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

def getixconn(s):
    conn = s[-1:]
    try: 
        ix = int(s[:-1])
    except ValueError:
        ix = -1
    return ix, conn

def generate_circuit(numnodes, indata, outdata):
    inputs = [(-1, "X")]
    inputs.extend([(i, "L") for i in range(numnodes)])
    inputs.extend([(i, "R") for i in range(numnodes)])
    outputs = [(i, "L") for i in range(numnodes)]
    outputs.extend([(i, "R") for i in range(numnodes)])
    outputs.append((-1, "X"))
    permutations = itertools.permutations(outputs)       
    num = 0
    gates = [Gate("", "", "", "") for i in range(numnodes)]
    for p in permutations:
        extin = (-1, "X")
        extout = (-1, "X")
        ok = True
        for ix in range(2*numnodes+1):
            outix, outconn = outputs[ix]
            inix, inconn = inputs[ix]
            if outix == -1 and inix == -1:
                ok = False
                break
            
            # Connect g[outix][outconn] -> g[inix][inconn]
            if outix != -1:
                g = gates[outix]
                if outconn == "L":
#                    print "set left out on", outix, inix, inconn
                    g.leftoutix = inix
                    g.leftoutconn = inconn
                elif outconn == "R":
#                    print "set right out on ", outix, inix, inconn
                    g.rightoutix = inix
                    g.rightoutconn = inconn
            if inix != -1:
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
            if outix == -1:
                extin = (inix, inconn)                      

            # Connect g[outix][outconn] -> X
            if inix == -1:
                extout = (outix, outconn)
            
        if ok:
            # print "%s:"%extin
            # gs = [str(g) for g in gates]
            # s= ",\n".join(gs) + ":"
            # print s
            # print extout
            # print

            num += 1
            if (num % 10000) == 0:
                print num
            out = calculate(gates, extin, extout, indata, outdata)
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

    def getval(self, conn):
        if conn == "L":
            return self.L
        elif conn == "R":
            return self.R
        else:
            raise InvalidConnector

    def __str__(self):
        leftinp = "X"
        if self.leftinix != -1:
            leftinp = "%d%s"%(self.leftinix, self.leftinconn)
        rightinp = "X"
        if self.rightinix != -1:
            rightinp = "%d%s"%(self.rightinix, self.rightinconn)
        leftoutp = "X"
        if self.leftoutix != -1:
            leftoutp = "%d%s"%(self.leftoutix, self.leftoutconn)
        rightoutp = "X"
        if self.rightoutix != -1:
            rightoutp = "%d%s"%(self.rightoutix, self.rightoutconn)
        return leftinp + rightinp + "0#" + leftoutp + rightoutp
        # return "'%s' '%s' '%s' '%s' '%s' '%s' '%s' '%s'"%(str(self.leftinix), str(self.leftinconn),
        #                                                   str(self.rightinix), str(self.rightinconn),
        #                                                   str(self.leftoutix), str(self.leftoutconn),
        #                                                   str(self.rightoutix), str(self.rightoutconn
                                                                                    # ))

def calculate(gates, extin, extout, inp, wanted):
    outp = []
    outix, extconn = extout
    for s, inval in enumerate(inp):
        for i, g in enumerate(gates):
            if g.leftinix != -1:
                lval = gates[g.leftinix].getval(g.leftinconn)
            else:
                lval = inval
            if g.rightinix != -1:
                rval = gates[g.rightinix].getval(g.rightinconn)
            else:
                rval = inval
            g.calc(lval, rval)
        val = gates[outix].getval(extconn)
        if val != wanted[s]:
            return
        outp.append(val)
    return outp

def main():
    for i in range(6, 1000):
        print "trying", i
        res = generate_circuit(i, 
                               [0,1,2,0,2,1,0,1,2,1,0,2,0,1,2,0,2],
                               [1,1,0,2,1,2,1,0,1,1,2,1,0,1,2,2,1])
        if res:
            break

if __name__=="__main__":
    main()
