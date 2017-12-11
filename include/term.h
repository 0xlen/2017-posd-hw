#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

template <class T>
class Iterator;

class Term {

    public:
        virtual string symbol() const = 0;

        virtual string value() const {
            return symbol();
        }

        virtual bool match(Term &term) {
            return symbol() == term.symbol();
        }

        virtual int arity() {
            return 0;
        }

        virtual Term *args(int index) {
            return nullptr;
        }

        virtual Iterator<Term *> *createIterator();
        virtual Iterator<Term *> *createDFSIterator();
        virtual Iterator<Term *> *createBFSIterator();
};

#endif
