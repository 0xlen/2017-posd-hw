#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using namespace std;

template <class T>
class Iterator;

class Struct : public Term
{
    public:
        Struct(Atom const & name, std::vector<Term *> args);

        Atom const & name();
        int arity();
        Term *args(int index);
        string symbol() const;
        bool match(Term &term);
        string value() const;

        Iterator<Term *> *createIterator();
        Iterator<Term *> *createDFSIterator();
        Iterator<Term *> *createBFSIterator();

    private:
        Atom _name;
        vector<Term *> _args;
};

#endif
