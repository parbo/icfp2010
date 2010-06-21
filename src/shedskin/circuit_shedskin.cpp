#include "circuit_shedskin.hpp"

namespace __circuit_shedskin__ {

str *const_0, *const_1, *const_10, *const_11, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

str *__name__;
dict<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *> *gatetable;

void * default_0;

static inline list<tuple2<__ss_int, str *> *> *list_comp_0(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_1(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_2(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_3(__ss_int numnodes);
static inline list<Gate *> *list_comp_4(__ss_int numnodes);
static inline list<str *> *list_comp_5(list<Gate *> *gates);

static inline list<tuple2<__ss_int, str *> *> *list_comp_0(__ss_int numnodes) {
    __ss_int i, __1, __2;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,1,2)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_0)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_1(__ss_int numnodes) {
    __ss_int i, __4, __3;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,3,4)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_1)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_2(__ss_int numnodes) {
    __ss_int i, __5, __6;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,5,6)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_0)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_3(__ss_int numnodes) {
    __ss_int i, __7, __8;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,7,8)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_1)));
    END_FOR

    return __ss_result;
}

static inline list<Gate *> *list_comp_4(__ss_int numnodes) {
    __ss_int i, __10, __9;
    list<Gate *> *__ss_result = new list<Gate *>();

    FAST_FOR(i,0,numnodes,1,9,10)
        __ss_result->append((new Gate(const_2, const_2, const_2, const_2)));
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_5(list<Gate *> *gates) {
    __ss_int __23;
    Gate *g;
    list<Gate *> *__21;
    __iter<Gate *> *__22;
    list<Gate *>::for_in_loop __24;
    list<str *> *__ss_result = new list<str *>();

    __ss_result->resize(len(gates));
    FOR_IN_NEW(g,gates,21,23,24)
        __ss_result->units[__23] = __str(g);
    END_FOR

    return __ss_result;
}

tuple2<__ss_int, str *> *getixconn(str *s) {
    str *conn;
    __ss_int ix;

    conn = s->__slice__(1, (-1), 0, 0);
    try {
        ix = __int(s->__slice__(2, 0, (-1), 0));
    } catch (ValueError *) {
        ix = (-1);
    }
    return (new tuple2<__ss_int, str *>(2, ix, conn));
}

__ss_bool generate_circuit(__ss_int numnodes, list<__ss_int> *indata, list<__ss_int> *outdata) {
    list<str *> *gs;
    __iter<tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *>::for_in_loop __14;
    __iter<tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *> *__11, *__12, *permutations;
    Gate *g;
    __ss_bool __19, __20, ok;
    list<tuple2<__ss_int, str *> *> *inputs, *outputs;
    str *inconn, *outconn, *s;
    tuple2<__ss_int, str *> *__17, *__18, *extin, *extout;
    list<__ss_int> *out;
    list<Gate *> *gates;
    __ss_int __13, __15, __16, inix, ix, num, outix;
    tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *p;

    inputs = (new list<tuple2<__ss_int, str *> *>(1, (new tuple2<__ss_int, str *>(2, (-1), const_3))));
    inputs->extend(list_comp_0(numnodes));
    inputs->extend(list_comp_1(numnodes));
    outputs = list_comp_2(numnodes);
    outputs->extend(list_comp_3(numnodes));
    outputs->append((new tuple2<__ss_int, str *>(2, (-1), const_3)));
    permutations = __itertools__::permutations(outputs, ((void *)(NULL)));
    num = 0;
    gates = list_comp_4(numnodes);

    FOR_IN_NEW(p,permutations,11,13,14)
        extin = (new tuple2<__ss_int, str *>(2, (-1), const_3));
        extout = (new tuple2<__ss_int, str *>(2, (-1), const_3));
        ok = True;

        FAST_FOR(ix,0,((2*numnodes)+1),1,15,16)
            __17 = outputs->__getfast__(ix);
            outix = __17->__getfirst__();
            outconn = __17->__getsecond__();
            __18 = inputs->__getfast__(ix);
            inix = __18->__getfirst__();
            inconn = __18->__getsecond__();
            if (((outix==(-1)) and (inix==(-1)))) {
                ok = False;
                break;
            }
            if ((outix!=(-1))) {
                g = gates->__getfast__(outix);
                if (__eq(outconn, const_0)) {
                    g->leftoutix = inix;
                    g->leftoutconn = inconn;
                }
                else if (__eq(outconn, const_1)) {
                    g->rightoutix = inix;
                    g->rightoutconn = inconn;
                }
            }
            if ((inix!=(-1))) {
                g = gates->__getfast__(inix);
                g->L = 0;
                g->R = 0;
                if (__eq(inconn, const_0)) {
                    g->leftinix = outix;
                    g->leftinconn = outconn;
                }
                else if (__eq(inconn, const_1)) {
                    g->rightinix = outix;
                    g->rightinconn = outconn;
                }
            }
            if ((outix==(-1))) {
                extin = (new tuple2<__ss_int, str *>(2, inix, inconn));
            }
            if ((inix==(-1))) {
                extout = (new tuple2<__ss_int, str *>(2, outix, outconn));
            }
        END_FOR

        if (ok) {
            num = (num+1);
            if ((__mods(num, 10000)==0)) {
                print2(0,1, ___box(num));
            }
            out = calculate(gates, extin, extout, indata, outdata);
            if (__eq(out, outdata)) {
                print2(0,0);
                print2(0,1, const_4);
                print2(0,1, indata);
                print2(0,1, outdata);
                print2(0,0);
                print2(0,1, __modtuple(const_5, extin));
                gs = list_comp_5(gates);
                s = ((const_6)->join(gs))->__add__(const_7);
                print2(0,1, s);
                print2(0,1, __modtuple(const_8, extout));
                print2(0,0);
                return True;
            }
        }
    END_FOR

    return False;
}

/**
class InvalidConnector
*/

class_ *cl_InvalidConnector;

/**
class Gate
*/

class_ *cl_Gate;

__ss_int Gate::getval(str *conn) {
    
    if (__eq(conn, const_0)) {
        return this->L;
    }
    else if (__eq(conn, const_1)) {
        return this->R;
    }
    else {
        throw (new InvalidConnector());
    }
    return 0;
}

str *Gate::__str__() {
    str *leftinp, *leftoutp, *rightinp, *rightoutp;

    leftinp = const_3;
    if ((this->leftinix!=(-1))) {
        leftinp = __modct(const_8, 2, ___box(this->leftinix), this->leftinconn);
    }
    rightinp = const_3;
    if ((this->rightinix!=(-1))) {
        rightinp = __modct(const_8, 2, ___box(this->rightinix), this->rightinconn);
    }
    leftoutp = const_3;
    if ((this->leftoutix!=(-1))) {
        leftoutp = __modct(const_8, 2, ___box(this->leftoutix), this->leftoutconn);
    }
    rightoutp = const_3;
    if ((this->rightoutix!=(-1))) {
        rightoutp = __modct(const_8, 2, ___box(this->rightoutix), this->rightoutconn);
    }
    return __add_strs(5, leftinp, rightinp, const_9, leftoutp, rightoutp);
}

void *Gate::calc(__ss_int left, __ss_int right) {
    tuple2<__ss_int, __ss_int> *__29;

    __29 = gatetable->__getitem__((new tuple2<__ss_int, __ss_int>(2, left, right)));
    this->L = __29->__getfirst__();
    this->R = __29->__getsecond__();
    return NULL;
}

void *Gate::__init__(str *iL, str *iR, str *oL, str *oR) {
    tuple2<__ss_int, str *> *__25, *__26, *__27, *__28;

    __25 = getixconn(iL);
    this->leftinix = __25->__getfirst__();
    this->leftinconn = __25->__getsecond__();
    __26 = getixconn(iR);
    this->rightinix = __26->__getfirst__();
    this->rightinconn = __26->__getsecond__();
    __27 = getixconn(oL);
    this->leftoutix = __27->__getfirst__();
    this->leftoutconn = __27->__getsecond__();
    __28 = getixconn(oR);
    this->rightoutix = __28->__getfirst__();
    this->rightoutconn = __28->__getsecond__();
    this->L = 0;
    this->R = 0;
    return NULL;
}

list<__ss_int> *calculate(list<Gate *> *gates, tuple2<__ss_int, str *> *extin, tuple2<__ss_int, str *> *extout, list<__ss_int> *inp, list<__ss_int> *wanted) {
    tuple2<__ss_int, __ss_int> *__31;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __36;
    Gate *g;
    list<__ss_int> *__35, *outp;
    tuple2<__ss_int, str *> *__30;
    __iter<tuple2<__ss_int, Gate *> *> *__38, *__39;
    str *extconn;
    list<Gate *> *__41;
    __iter<tuple2<__ss_int, Gate *> *>::for_in_loop __42;
    __iter<tuple2<__ss_int, __ss_int> *> *__32, *__33;
    __ss_int __34, __40, i, inval, lval, outix, rval, s, val;
    tuple2<__ss_int, Gate *> *__37;

    outp = (new list<__ss_int>());
    __30 = extout;
    outix = __30->__getfirst__();
    extconn = __30->__getsecond__();

    FOR_IN_SEQ(inval,inp,35,34)
        s = __34;

        FOR_IN_SEQ(g,gates,41,40)
            i = __40;
            if ((g->leftinix!=(-1))) {
                lval = (gates->__getfast__(g->leftinix))->getval(g->leftinconn);
            }
            else {
                lval = inval;
            }
            if ((g->rightinix!=(-1))) {
                rval = (gates->__getfast__(g->rightinix))->getval(g->rightinconn);
            }
            else {
                rval = inval;
            }
            g->calc(lval, rval);
        END_FOR

        val = (gates->__getfast__(outix))->getval(extconn);
        if ((val!=wanted->__getfast__(s))) {
            return ((list<__ss_int> *)(NULL));
        }
        outp->append(val);
    END_FOR

    return outp;
}

void *__ss_main() {
    __ss_bool res;
    __ss_int __43, __44, i;


    FAST_FOR(i,6,1000,1,43,44)
        print2(0,2, const_10, ___box(i));
        res = generate_circuit(i, (new list<__ss_int>(17, 0, 1, 2, 0, 2, 1, 0, 1, 2, 1, 0, 2, 0, 1, 2, 0, 2)), (new list<__ss_int>(17, 1, 1, 0, 2, 1, 2, 1, 0, 1, 1, 2, 1, 0, 1, 2, 2, 1)));
        if (res) {
            break;
        }
    END_FOR

    return NULL;
}

void __init() {
    const_0 = new str("L");
    const_1 = new str("R");
    const_2 = new str("");
    const_3 = new str("X");
    const_4 = new str("Solution for:");
    const_5 = new str("%d%s:");
    const_6 = new str(",\n");
    const_7 = new str(":");
    const_8 = new str("%d%s");
    const_9 = new str("0#");
    const_10 = new str("trying");
    const_11 = new str("__main__");

    __name__ = new str("__main__");

    gatetable = (new dict<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(9, new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0, 0)),(new tuple2<__ss_int, __ss_int>(2, 0, 2))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0, 1)),(new tuple2<__ss_int, __ss_int>(2, 2, 2))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0, 2)),(new tuple2<__ss_int, __ss_int>(2, 1, 2))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1, 0)),(new tuple2<__ss_int, __ss_int>(2, 1, 2))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1, 1)),(new tuple2<__ss_int, __ss_int>(2, 0, 0))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1, 2)),(new tuple2<__ss_int, __ss_int>(2, 2, 1))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2, 0)),(new tuple2<__ss_int, __ss_int>(2, 2, 2))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2, 1)),(new tuple2<__ss_int, __ss_int>(2, 1, 1))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2, 2)),(new tuple2<__ss_int, __ss_int>(2, 0, 0)))));
    cl_InvalidConnector = new class_("InvalidConnector", 45, 45);
    cl_Gate = new class_("Gate", 6, 6);
    if (__eq(__name__, const_11)) {
        __ss_main();
    }
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __itertools__::__init();
    __shedskin__::__start(__circuit_shedskin__::__init);
}
