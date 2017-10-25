#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>

using std::vector;

class List : public Term
{
    public:
        List(): _elements() {}
        List(vector<Term *> const &elements): _elements(elements) {}

        string symbol() const {
            string symbol = "";

            symbol += "[";
            for (int i = 0; i < _elements.size(); i++) {
                string delimiter = ", ";
                if (i == _elements.size() - 1) {
                    delimiter = "";
                }

                symbol += _elements[i]->symbol() + delimiter;
            }
            symbol += "]";

            return symbol;
        }

        string value() const {
            string value = "";

            value += "[";
            for (int i = 0; i < _elements.size(); i++) {
                string delimiter = ", ";
                if (i == _elements.size() - 1) {
                    delimiter = "";
                }

                value += _elements[i]->value() + delimiter;
            }
            value += "]";

            return value;
        }

        bool match(Term & term) {
            List* list = dynamic_cast<List *> (&term);
            Variable* variable = dynamic_cast<Variable *> (&term);

            if (list) {
                if (_elements.size() == list->size())  {

                    for (int i = 0; i < _elements.size(); i++) {
                        if(! _elements[i]->match( list->get(i) )) return false;
                    }

                    return true;
                }
            }

            if (variable) {
                return variable->match(*this);
            }

            return false;
        }

        Term * head() const {
            if (! _elements.empty()) {
                return _elements[0];
            } else {
                throw string("Accessing head in an empty list");
            }
        }

        List * tail() const {
            if (! _elements.empty()) {
                vector<Term *> newElements(_elements.begin()+ 1, _elements.end());

                return new List(newElements);
            } else {
                throw string("Accessing tail in an empty list");
            }
        }

        int size() {
            return _elements.size();
        }

        Term & get(int i) {
            return *_elements[i];
        }

    private:
        vector<Term *> _elements;
};

#endif
