#include "list.h"


string List::symbol(){
    string description = "[";
    if(_elements.size()==0) description = "[]";
    else{
        for(int i=0; i<_elements.size(); i++){
            if(i != _elements.size() - 1)description += _elements[i]->symbol() + ", ";
            else description += _elements[i]->symbol() + "]";
        }
    }
    return description;
}

string List::value(){
    string description = "[";
    if(_elements.size()==0) description = "[]";
    else{
        for(int i=0; i<_elements.size(); i++){
            if(i != _elements.size() - 1)description += _elements[i]->value() + ", ";
            else description += _elements[i]->value() + "]";
        }
    }
    return description;
}

bool List::match(Term &term){
    bool isTrue = false;
    if(this == &term) return true;
    else if(_elements.size() == 0){
        _elements.push_back(&term);
        return true;
    }
    else{
        List *tempList = dynamic_cast<List *>(&term);
        if(tempList){
            for(int i=0; i<_elements.size(); i++){
                if(_elements[i]->symbol() == tempList->getElement(i).symbol()){
                    isTrue = true;
                    continue;
                }
                if(_elements[i]->match(tempList->getElement(i))){
                    isTrue = true;
                }
                else{
                    isTrue=false;
                }
            }
        }
        return isTrue;
    }
}

bool List::match(Variable &variable){
    if(_elements.size() != 0){
        for(int i=0; i<_elements.size(); i++){
            if(_elements[i] == &variable) return false;
        }
    }
    if(variable.getAssignable()){
        variable.setValue(this);
        return true;
    }
    else{
        return symbol() == variable.value();
    }
}

Term &List::getElement(int index){
    return *_elements[index];
}

Term *List::head() const{
    if (_elements.size() != 0) return _elements[0];
    else throw(std::string("Accessing head in an empty list"));
}

List *List::tail() const{
    if (_elements.size() != 0){
        vector<Term *> v = {};
        for(int i=1; i<_elements.size(); i++) v.push_back(_elements[i]);
        List *tail = new List(v);
        return tail;
    }
    else throw(std::string("Accessing tail in an empty list"));
}
