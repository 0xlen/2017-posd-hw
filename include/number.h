#ifndef NUMBER_H
#define NUMBER_H

#include "variable.h"
#include "atom.h"
#include <string>

class Atom;
class Variable;

using std::string;

class Number {
    public:
        Number (int number) {
            _value = std::to_string(number);
        }

        string symbol() {
            return _symbol;
        }

        string value();

        bool match(Atom &atom);
        bool match(Number &number);
        bool match(Variable &variable);

    private:
        string _symbol;
        string _value;
};

#endif
