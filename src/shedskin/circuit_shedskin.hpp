#ifndef __CIRCUIT_SHEDSKIN_HPP
#define __CIRCUIT_SHEDSKIN_HPP

#include "builtin.hpp"
#include "itertools.hpp"
#include "sys.hpp"
#include "circuit_shedskin.hpp"

using namespace __shedskin__;
namespace __circuit_shedskin__ {

extern str *const_0, *const_1, *const_10, *const_11, *const_12, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;


class InvalidConnector;
class Gate;


extern str *__name__;
extern dict<tuple2<__ss_int, __ss_int> *, tuple2<__ss_int, __ss_int> *> *gatetable;

extern class_ *cl_InvalidConnector;
class InvalidConnector : public Exception {
public:
    InvalidConnector() { this->__class__ = cl_InvalidConnector; }
};

extern class_ *cl_Gate;
class Gate : public object {
public:
    __ss_int leftinix;
    str *leftoutconn;
    str *leftinconn;
    __ss_int rightinix;
    __ss_int R;
    str *rightinconn;
    __ss_int leftoutix;
    str *rightoutconn;
    __ss_int rightoutix;
    __ss_int L;

    Gate() {}
    Gate(str *iL, str *iR, str *oL, str *oR) {
        this->__class__ = cl_Gate;
        __init__(iL, iR, oL, oR);
    }
    __ss_int getval(str *conn);
    str *__str__();
    void *calc(__ss_int left, __ss_int right);
    void *__init__(str *iL, str *iR, str *oL, str *oR);
};

extern void * default_0;

tuple2<__ss_int, str *> *getixconn(str *s);
__ss_bool generate_circuit(__ss_int numnodes, list<__ss_int> *indata, list<__ss_int> *outdata);
__ss_bool calculate(list<Gate *> *gates, tuple2<__ss_int, str *> *extin, tuple2<__ss_int, str *> *extout, list<__ss_int> *inp, list<__ss_int> *wanted);
void *__ss_main();

} // module namespace
#endif
