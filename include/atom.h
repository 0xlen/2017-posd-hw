#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "variable.h"
#include "term.h"

using std::string;

class Atom : public Term {

    public:
        Atom();
        Atom(string str);

        string symbol() const;
        bool match(Term &term);
        bool match(Variable &variable);

    private:
        string _symbol;
};

#endif
