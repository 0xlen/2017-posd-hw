#include "number.h"

string Number::value(){
    return _value;
}

string Number::symbol(){
    return _symbol;
}

bool Number::match(Variable &variable){
     if(variable.getAssignable()){
         variable.setValue(this);
         return true;
     }
     else{
        return value() == variable.value();
     }
}

bool Number::match(Term &term){
    return value() == term.value();
}

