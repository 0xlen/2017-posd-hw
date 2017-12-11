#include "include/number.h"
#include "include/iterator.h"


Number::Number (double number) {
    std::stringstream val;
    val << number;

    _symbol = val.str();
}

string Number::symbol() const {
    return _symbol;
}

bool Number::match(Term &term) {
    return value() == term.value();
}

bool Number::match(Variable &variable) {
    return variable.match(*this);
}

Iterator<Term *> *Number::createIterator()
{
    return new NullIterator<Term *>(this);
}

Iterator<Term *> *Number::createDFSIterator()
{
    return new NullIterator<Term *>(this);
}

Iterator<Term *> *Number::createBFSIterator()
{
    return new NullIterator<Term *>(this);
}

