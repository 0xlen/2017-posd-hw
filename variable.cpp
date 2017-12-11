#include "include/variable.h"


Variable::Variable(string s) {
    _symbol = s;
}

string Variable::value() const {
    if (_value) {
        return _value->value();
    } else {
        return symbol();
    }
}

bool Variable::match(Term &term) {
    if (&term == this) {
        return true;
    }

    if (_value == NULL) {
        _value = &term;
        return true;
    }

    return _value->match(term);
}

string Variable::symbol() const {
    return _symbol;
}
