#include "variable.h"
#include <iostream>

string Variable::value(){
    if(_value != NULL){
        return _value->value();
    }
    else{
        return symbol();
    }
}

string Variable::symbol(){return _symbol;}


void Variable::setValue(Term *value){
    _value = value;
}


bool Variable::match(Term &term){
    if(this == &term) return true;
    else if(_value == NULL){
        _value = &term;
        return true;
    }
    else{
        Variable *tempVar = dynamic_cast<Variable*>(&term);
        if(tempVar != nullptr){
            if(tempVar->getAssignable()){
                tempVar->setValue(_value);
                return true;
            }
            else _value->match(*tempVar);
        }
        return _value->match(term);
    }
 }

 bool Variable::getAssignable(){
    if(_value == NULL) return true;
    else return false;
 }

