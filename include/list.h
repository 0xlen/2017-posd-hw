#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>

using std::vector;


template <class T>
class Iterator;

class List : public Term
{
    public:
        List();
        List(vector<Term *> const &elements);

        string symbol() const;
        string value() const;
        Term * head() const;
        List * tail() const;

        int size();
        bool match(Term & term);
        Term & get(int i);

        Iterator<Term *> *createIterator();
        Iterator<Term *> *createDFSIterator();
        Iterator<Term *> *createBFSIterator();

    private:
        vector<Term *> _elements;
};

#endif
