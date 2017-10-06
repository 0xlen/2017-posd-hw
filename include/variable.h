#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "number.h"
#include "atom.h"

using std::string;

class Variable{
    public:
        Variable(string s): _symbol(s) {}
        string value() { return _value; }

        bool match(Atom atom);
        bool match(Number number);
        string symbol();

    private:
        string _value;
        bool _assignable = true;
        string const _symbol;
};

#endif
