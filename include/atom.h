#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <number.h>
#include <variable.h>

using std::string;

class Atom {

    public:
        Atom (string str): _symbol(str) {}

        string value() {
            return _value;
        }

        string symbol() {
            return _symbol;
        }

        bool match(Atom atom);
        bool match(Number number);
        bool match(Variable &variable);

        bool operator==(Atom atom) {
            return _symbol == atom._symbol;
        }

    private:
        string _symbol;
        string _value;
};

#endif
