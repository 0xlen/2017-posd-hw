#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
#include "term.h"
#include <vector>

using std::string;
class Atom;
class Number;
class Term;

class Variable : public Term {
    public:
        string const _symbol;
        Variable(string s):_symbol(s), _value(NULL){}
        string symbol();
        string value();
        bool match(Term &term);
        void setValue(Term *value);
        bool getAssignable();
    private:
        Term* _value;
};

#endif
