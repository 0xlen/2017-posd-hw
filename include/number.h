#ifndef NUMBER_H
#define NUMBER_H

#include "variable.h"
#include "term.h"
#include <string>
#include <sstream>

using std::string;

class Number : public Term {
    public:
        Number (double number);

        string symbol() const;
        bool match(Term &term);
        bool match(Variable &variable);

        Iterator<Term *> *createIterator();
        Iterator<Term *> *createDFSIterator();
        Iterator<Term *> *createBFSIterator();

    private:
        string _symbol;
};

#endif
