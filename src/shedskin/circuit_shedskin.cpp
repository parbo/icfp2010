#include "circuit_shedskin.hpp"

namespace __circuit_shedskin__ {

str *const_0, *const_1, *const_10, *const_11, *const_12, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

str *__name__;
dict<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *> *gatetable;

void * default_0;

static inline list<tuple2<__ss_int, str *> *> *list_comp_0(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_1(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_2(__ss_int numnodes);
static inline list<tuple2<__ss_int, str *> *> *list_comp_3(__ss_int numnodes);
static inline list<Gate *> *list_comp_4(__ss_int numnodes);
static inline list<str *> *list_comp_5(list<Gate *> *gates);
static inline list<__ss_int> *list_comp_6();
static inline list<__ss_int> *list_comp_7();

static inline list<tuple2<__ss_int, str *> *> *list_comp_0(__ss_int numnodes) {
    __ss_int i, __4, __5;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,4,5)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_0)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_1(__ss_int numnodes) {
    __ss_int i, __7, __6;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,6,7)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_1)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_2(__ss_int numnodes) {
    __ss_int i, __9, __8;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,8,9)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_0)));
    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_3(__ss_int numnodes) {
    __ss_int i, __10, __11;
    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    FAST_FOR(i,0,numnodes,1,10,11)
        __ss_result->append((new tuple2<__ss_int, str *>(2, i, const_1)));
    END_FOR

    return __ss_result;
}

static inline list<Gate *> *list_comp_4(__ss_int numnodes) {
    __ss_int i, __13, __12;
    list<Gate *> *__ss_result = new list<Gate *>();

    FAST_FOR(i,0,numnodes,1,12,13)
        __ss_result->append((new Gate(const_2, const_2, const_2, const_2)));
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_5(list<Gate *> *gates) {
    Gate *g;
    __ss_int __26;
    __iter<Gate *> *__25;
    list<Gate *> *__24;
    list<Gate *>::for_in_loop __27;
    list<str *> *__ss_result = new list<str *>();

    __ss_result->resize(len(gates));
    FOR_IN_NEW(g,gates,24,26,27)
        __ss_result->units[__26] = __str(g);
    END_FOR

    return __ss_result;
}

static inline list<__ss_int> *list_comp_6() {
    str *x, *__46;
    __ss_int __48;
    __iter<str *> *__47;
    str::for_in_loop __49;
    list<__ss_int> *__ss_result = new list<__ss_int>();

    __46 = (__sys__::argv)->__getfast__(2LL);
    __ss_result->resize(len(__46));
    FOR_IN_NEW(x,__46,46,48,49)
        __ss_result->units[__48] = __int(x);
    END_FOR

    return __ss_result;
}

static inline list<__ss_int> *list_comp_7() {
    str *x, *__50;
    __ss_int __52;
    __iter<str *> *__51;
    str::for_in_loop __53;
    list<__ss_int> *__ss_result = new list<__ss_int>();

    __50 = (__sys__::argv)->__getfast__(3LL);
    __ss_result->resize(len(__50));
    FOR_IN_NEW(x,__50,50,52,53)
        __ss_result->units[__52] = __int(x);
    END_FOR

    return __ss_result;
}

tuple2<__ss_int, str *> *getixconn(str *s) {
    str *conn;
    __ss_int ix;

    conn = s->__slice__(1LL, (-1LL), 0LL, 0LL);
    try {
        ix = __int(s->__slice__(2LL, 0LL, (-1LL), 0LL));
    } catch (ValueError *) {
        ix = (-1LL);
    }
    return (new tuple2<__ss_int, str *>(2, ix, conn));
}

__ss_bool generate_circuit(__ss_int numnodes, list<__ss_int> *indata, list<__ss_int> *outdata) {
    list<str *> *gs;
    __iter<tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *>::for_in_loop __17;
    __iter<tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *> *__14, *__15, *permutations;
    Gate *g;
    __ss_bool __22, __23, ok, res;
    list<tuple2<__ss_int, str *> *> *inputs, *outputs;
    tuple2<__ss_int, str *> *__20, *__21, *extin, *extout;
    str *inconn, *outconn, *s;
    list<Gate *> *gates;
    __ss_int __16, __18, __19, inix, ix, num, outix;
    tuple2<tuple2<__ss_int, str *> *, tuple2<__ss_int, str *> *> *p;

    inputs = (new list<tuple2<__ss_int, str *> *>(1, (new tuple2<__ss_int, str *>(2, (-1LL), const_3))));
    inputs->extend(list_comp_0(numnodes));
    inputs->extend(list_comp_1(numnodes));
    outputs = list_comp_2(numnodes);
    outputs->extend(list_comp_3(numnodes));
    outputs->append((new tuple2<__ss_int, str *>(2, (-1LL), const_3)));
    permutations = __itertools__::permutations(outputs, ((void *)(NULL)));
    num = 0LL;
    gates = list_comp_4(numnodes);

    FOR_IN_NEW(p,permutations,14,16,17)
        extin = (new tuple2<__ss_int, str *>(2, (-1LL), const_3));
        extout = (new tuple2<__ss_int, str *>(2, (-1LL), const_3));
        ok = True;

        FAST_FOR(ix,0,((2LL*numnodes)+1LL),1,18,19)
            __20 = p->__getfast__(ix);
            outix = __20->__getfirst__();
            outconn = __20->__getsecond__();
            __21 = inputs->__getfast__(ix);
            inix = __21->__getfirst__();
            inconn = __21->__getsecond__();
            if (((outix==(-1LL)) and (inix==(-1LL)))) {
                ok = False;
                break;
            }
            if ((outix!=(-1LL))) {
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
            if ((inix!=(-1LL))) {
                g = gates->__getfast__(inix);
                g->L = 0LL;
                g->R = 0LL;
                if (__eq(inconn, const_0)) {
                    g->leftinix = outix;
                    g->leftinconn = outconn;
                }
                else if (__eq(inconn, const_1)) {
                    g->rightinix = outix;
                    g->rightinconn = outconn;
                }
            }
            if ((outix==(-1LL))) {
                extin = (new tuple2<__ss_int, str *>(2, inix, inconn));
            }
            if ((inix==(-1LL))) {
                extout = (new tuple2<__ss_int, str *>(2, outix, outconn));
            }
        END_FOR

        num = (num+1LL);
        if ((__mods(num, 1000000LL)==0LL)) {
            print2(0,1, ___box(num));
        }
        if (ok) {
            res = calculate(gates, extin, extout, indata, outdata);
            if (res) {
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
    if ((this->leftinix!=(-1LL))) {
        leftinp = __modct(const_8, 2, ___box(this->leftinix), this->leftinconn);
    }
    rightinp = const_3;
    if ((this->rightinix!=(-1LL))) {
        rightinp = __modct(const_8, 2, ___box(this->rightinix), this->rightinconn);
    }
    leftoutp = const_3;
    if ((this->leftoutix!=(-1LL))) {
        leftoutp = __modct(const_8, 2, ___box(this->leftoutix), this->leftoutconn);
    }
    rightoutp = const_3;
    if ((this->rightoutix!=(-1LL))) {
        rightoutp = __modct(const_8, 2, ___box(this->rightoutix), this->rightoutconn);
    }
    return __add_strs(5, leftinp, rightinp, const_9, leftoutp, rightoutp);
}

void *Gate::calc(__ss_int left, __ss_int right) {
    tuple2<__ss_int, __ss_int> *__32;

    __32 = gatetable->__getitem__((new tuple2<__ss_int, __ss_int>(2, left, right)));
    this->L = __32->__getfirst__();
    this->R = __32->__getsecond__();
    return NULL;
}

void *Gate::__init__(str *iL, str *iR, str *oL, str *oR) {
    tuple2<__ss_int, str *> *__28, *__29, *__30, *__31;

    __28 = getixconn(iL);
    this->leftinix = __28->__getfirst__();
    this->leftinconn = __28->__getsecond__();
    __29 = getixconn(iR);
    this->rightinix = __29->__getfirst__();
    this->rightinconn = __29->__getsecond__();
    __30 = getixconn(oL);
    this->leftoutix = __30->__getfirst__();
    this->leftoutconn = __30->__getsecond__();
    __31 = getixconn(oR);
    this->rightoutix = __31->__getfirst__();
    this->rightoutconn = __31->__getsecond__();
    this->L = 0LL;
    this->R = 0LL;
    return NULL;
}

__ss_bool calculate(list<Gate *> *gates, tuple2<__ss_int, str *> *extin, tuple2<__ss_int, str *> *extout, list<__ss_int> *inp, list<__ss_int> *wanted) {
    tuple2<__ss_int, __ss_int> *__34;
    __iter<tuple2<__ss_int, __ss_int> *>::for_in_loop __39;
    list<Gate *>::for_in_loop __43;
    Gate *g;
    list<__ss_int> *__38;
    tuple2<__ss_int, str *> *__33;
    str *extconn;
    list<Gate *> *__40;
    __iter<tuple2<__ss_int, __ss_int> *> *__35, *__36;
    __ss_int __37, __42, inval, lval, outix, rval, s, val;
    __iter<Gate *> *__41;

    __33 = extout;
    outix = __33->__getfirst__();
    extconn = __33->__getsecond__();

    FOR_IN_SEQ(inval,inp,38,37)
        s = __37;

        FOR_IN_NEW(g,gates,40,42,43)
            if ((g->leftinix!=(-1LL))) {
                lval = (gates->__getfast__(g->leftinix))->getval(g->leftinconn);
            }
            else {
                lval = inval;
            }
            if ((g->rightinix!=(-1LL))) {
                rval = (gates->__getfast__(g->rightinix))->getval(g->rightinconn);
            }
            else {
                rval = inval;
            }
            g->calc(lval, rval);
        END_FOR

        val = (gates->__getfast__(outix))->getval(extconn);
        if ((val!=wanted->__getfast__(s))) {
            return False;
        }
    END_FOR

    return True;
}

void *__ss_main() {
    __ss_bool res;
    __ss_int __44, __45, i, numnodes;

    numnodes = __int((__sys__::argv)->__getfast__(1LL));

    FAST_FOR(i,numnodes,1000LL,1,44,45)
        print2(0,3, const_10, ___box(i), const_11);
        res = generate_circuit(i, list_comp_6(), list_comp_7());
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
    const_10 = new str("Generating circuits with");
    const_11 = new str("nodes..");
    const_12 = new str("__main__");

    __name__ = new str("__main__");

    gatetable = (new dict<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(9, new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0LL, 0LL)),(new tuple2<__ss_int, __ss_int>(2, 0LL, 2LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0LL, 1LL)),(new tuple2<__ss_int, __ss_int>(2, 2LL, 2LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 0LL, 2LL)),(new tuple2<__ss_int, __ss_int>(2, 1LL, 2LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1LL, 0LL)),(new tuple2<__ss_int, __ss_int>(2, 1LL, 2LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1LL, 1LL)),(new tuple2<__ss_int, __ss_int>(2, 0LL, 0LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 1LL, 2LL)),(new tuple2<__ss_int, __ss_int>(2, 2LL, 1LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2LL, 0LL)),(new tuple2<__ss_int, __ss_int>(2, 2LL, 2LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2LL, 1LL)),(new tuple2<__ss_int, __ss_int>(2, 1LL, 1LL))), new tuple2<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *>(2,(new tuple2<__ss_int, __ss_int>(2, 2LL, 2LL)),(new tuple2<__ss_int, __ss_int>(2, 0LL, 0LL)))));
    cl_InvalidConnector = new class_("InvalidConnector", 37, 37);
    cl_Gate = new class_("Gate", 46, 46);
    if (__eq(__name__, const_12)) {
        __ss_main();
    }
}

} // module namespace

int main(int argc, char **argv) {
    __shedskin__::__init();
    __sys__::__init(argc, argv);
    __itertools__::__init();
    __shedskin__::__start(__circuit_shedskin__::__init);
}
