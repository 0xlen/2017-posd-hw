#include "struct.h"

Atom Struct::name(){return _name;}
int Struct::getTermSize(){return _term.size();}

Term* Struct::args(int index){
    return _term[index];
}

std::string Struct::symbol(){
    string description;
    description = _name.symbol() + "(";
    if(_term.size() == 0) return description + ")";
    for(int i=0; i<_term.size(); i++){
        if(i < _term.size()-1)
            description += _term[i]->symbol() + ", ";
        else
            description += _term[i]->symbol() + ")";
    }
    return description;
}



bool Struct::match(Term &term){
    Struct *struc = dynamic_cast<Struct *>(&term);
    bool judgement = true;
    if(struc != NULL){
        if(_name.symbol() != struc->name().symbol()) judgement = false;
        else{
            if( getTermSize() != struc->getTermSize()) judgement = false;
            else{
                for(int i=0; i<getTermSize(); i++){
                    if(_term[i]->symbol() != struc->args(i)->symbol()){
                        judgement = false;
                        break;
                    }
                }
            }
        }
    }
    else judgement = false;
    return judgement;
}
/*
bool Struct::match(Variable &variable){
    if(variable.getAssignable()){
        variable.setValue(this);
        return true;
    }
    else{
        return symbol() == variable.value();
    }
}
*/

std::string Struct::value(){
    string description;
    description = _name.symbol() + "(";
    for(int i=0; i<_term.size(); i++){
        if(i < _term.size()-1)
            description += _term[i]->value() + ", ";
        else
            description += _term[i]->value() + ")";
    }
    return description;
}

int Struct::arity(){
    return _term.size();
}
