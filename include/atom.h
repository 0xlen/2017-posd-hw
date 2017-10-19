#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "variable.h"
#include "term.h"

using std::string;

class Atom : public Term {

    public:
        Atom() {}

        Atom(string str) {
            _symbol = str;
        }

        string symbol() const {
            return _symbol;
        }

        bool match(Term &term) {
            return value() == term.value();
        }

        bool match(Variable &variable) {
            return variable.match(*this);
        }

    private:
        string _symbol;
};

#endif
