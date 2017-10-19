#ifndef NUMBER_H
#define NUMBER_H

#include "variable.h"
#include "term.h"
#include <string>
#include <sstream>

using std::string;

class Number : public Term {
    public:
        Number (double number) {
            std::stringstream val;
            val << number;

            _symbol = val.str();
        }

        string symbol() const {
            return _symbol;
        }

        bool match(Term &term) {
            return value() == term.value();
        }

        bool match(Variable &variable) {
            return variable.match(*this);
        }

    private:
        string _symbol;
};

#endif
