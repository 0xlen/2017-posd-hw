#include "atom.h"
#include "variable.h"
#include "number.h"


string Atom::value(){
    return _value;
}

string Atom::symbol(){
    return _symbol;
}

bool Atom::match(Term &term){
    return _value == term.value();
}

bool Atom::match(Variable &variable){
    if(variable.getAssignable()){
        variable.setValue(this);
        return true;
    }
    else{
        return value() == variable.value();
    }
}


