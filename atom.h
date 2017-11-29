#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "number.h"
#include "variable.h"
#include "term.h"

class Number;
class Variable;

class Atom : public Term {
public:
    Atom (string s):_symbol(s){ _value = s;}
    bool match(Term &term);
    bool match(Variable &variable);
    string value();
    string symbol();
private:
    string _value;
    string _symbol;
};

#endif
