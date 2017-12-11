#include "include/list.h"
#include "include/variable.h"
#include "include/iterator.h"

List::List() {
}

List::List(vector<Term *> const &elements) {
    _elements = elements;
}

string List::symbol() const {
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

string List::value() const {
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

bool List::match(Term & term) {
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

Term * List::head() const {
    if (! _elements.empty()) {
        return _elements[0];
    } else {
        throw string("Accessing head in an empty list");
    }
}

List * List::tail() const {
    if (! _elements.empty()) {
        vector<Term *> newElements(_elements.begin()+ 1, _elements.end());

        return new List(newElements);
    } else {
        throw string("Accessing tail in an empty list");
    }
}

int List::size() {
    return _elements.size();
}

Term & List::get(int i) {
    return *_elements[i];
}

Iterator<Term *> *List::createIterator()
{
    return new ListIterator<Term *>(this);
}

Iterator<Term *> *List::createDFSIterator()
{
    return new DFSIterator<Term *>(this);
}

Iterator<Term *> *List::createBFSIterator()
{
    return new BFSIterator<Term *>(this);
}

