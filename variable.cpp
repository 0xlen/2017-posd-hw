#include "include/variable.h"

bool Variable::match(Atom atom) {
    bool ret = _assignable || (_value == atom.value());

    if (_assignable) {
        _value = atom.value();
        _assignable = false;
    }

    return ret;
}

bool Variable::match(Number number) {
    bool ret = _assignable || (_value == number.value());

    if (_assignable) {
        _value = number.symbol();
        _assignable = false;
    }

    return ret;
}
