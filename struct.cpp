#include "include/struct.h"
#include "include/iterator.h"

Struct::Struct(Atom const & name, std::vector<Term *> args) {
    _name = name;
    _args = args;
}

Atom const & Struct::name() {
    return _name;
}

int Struct::arity() {
    return _args.size();
}

Term * Struct::args(int index) {
    return _args[index];
}

string Struct::symbol() const {

    string ret = _name.symbol() + "(";
    if (_args.empty()) {

        ret += ")";

    } else {

        for(int i = 0; i < _args.size() - 1 ; i++){
            ret += _args[i]-> symbol() + ", ";
        }
        ret += _args[_args.size()-1]-> symbol() + ")";

    }

    return  ret;
}

bool Struct::match(Term &term) {
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){

        if (!_name.match(ps->_name))
            return false;
        if(_args.size()!= ps->_args.size())
            return false;
        for(int i=0;i<_args.size();i++){
            if(_args[i]->symbol() != ps->_args[i]->symbol())
                return false;
        }

        return true;
    }

    return false;
}

string Struct::value() const {
    string val = "";

    val += _name.symbol();
    val += "(";

    for (int i = 0; i < _args.size() - 1; i++) {
        val += _args[i]->value();
        val += ", ";
    }

    val += _args[_args.size() - 1]->value();
    val += ")";

    return val;
}

Iterator<Term *> *Struct::createIterator() {
    return new StructIterator<Term *>(this);
}

Iterator<Term *> *Struct::createDFSIterator() {
    return new DFSIterator<Term *>(this);
}

Iterator<Term *> *Struct::createBFSIterator() {
    return new BFSIterator<Term *>(this);
}

