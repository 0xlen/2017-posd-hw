#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

using std::string;

class Variable : public Term{
    public:
        Variable(string s): _symbol(s) {}

        string value() const {
            if (_value) {
                return _value->value();
            } else {
                return symbol();
            }
        }

        bool match(Term &term) {
            if (&term == this) {
                return true;
            }

            if (_value == NULL) {
                _value = &term;
                return true;
            }

            return _value->match(term);
        }

        string symbol() const {
            return _symbol;
        }

    private:
        Term *_value = NULL;
        bool _assignable = true;
        string _symbol;
};

#endif
