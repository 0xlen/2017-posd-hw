#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include "term.h"
#include "atom.h"
#include "variable.h"
#include "number.h"
#include <vector>

class Struct : public Term{
    public:
        Struct(Atom atom, std::vector<Term *> term): _name(atom), _term(term){}
        std::string symbol();
        std::string value();
        bool match(Term &term);
        //bool match(Variable &variable);
        Atom name();
        Term* args(int index);
        int getTermSize();
        int arity();
    private:
        std::vector<Term *> _term;
        Atom _name;
};


#endif
