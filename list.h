#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <string>
#include "variable.h"

using std::vector;

class List : public Term {
    public:
        List():_elements(){
            vector<Term *> v = {};
            _elements = v;
        }
        List(vector<Term *> const & elements):_elements(elements){}
        string symbol();
        string value();
        bool match(Term & term);
        bool match(Variable &variable);
        Term * head() const;
        List * tail() const;
        Term &getElement(int index);
    private:
        vector<Term *> _elements;
};

#endif
