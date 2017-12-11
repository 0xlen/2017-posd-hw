#include "include/atom.h"


Atom::Atom() {
}

Atom::Atom(string str) {
    _symbol = str;
}

string Atom::symbol() const {
    return _symbol;
}

bool Atom::match(Term &term) {
    return value() == term.value();
}

bool Atom::match(Variable &variable) {
    return variable.match(*this);
}
