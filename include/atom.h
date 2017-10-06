#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Number;
class Variable;

class Atom {

    public:
        Atom (string str) {
            _symbol = str;
            _value = str;
        }

        string value() {
            return _value;
        }

        string symbol() {
            return _symbol;
        }

        bool match(Atom &atom);
        bool match(Number &number);
        bool match(Variable &variable);

    private:
        string _symbol;
        string _value;
};

#endif
