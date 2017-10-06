#include "include/number.h"

string Number::value() {
    return this->_value;
}

bool Number::match(Atom &atom) {
    return false;
}

bool Number::match(Number &number) {
    return (number.value() == this->value());
}

bool Number::match(Variable &variable) {
    return variable.match(*this);
}
