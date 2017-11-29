#include "parser.h"
#include <iostream>

Term* Parser::createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
        return new Variable(symtable[_scanner.tokenValue()].first);
    }
    else if(token == NUMBER){
        return new Number(_scanner.tokenValue());
    }
    else if(token == ATOM || token == ATOMSC){
        Atom* tempAtom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '('){
            _scanner.nextToken();
            vector<Term*> terms = getArgs();
            if(_currentToken == ')'){
                return new Struct(*tempAtom, terms);
            }
        }

        else
            return tempAtom;
    }
    else if(token == '['){
        vector<Term*> finalTerm = getArgs();
        if(_currentToken == ')') throw(std::string("unexpected token"));
        if(_currentToken == ']' || _currentToken == 0){
            List* l = new List(finalTerm);
            return l;
        }
    }
    return nullptr;
}

void Parser::matchings(){
    Term* term = createTerm();
    if(term!=nullptr){
        if(isCOMMA == 1){
            Term* findTerm = finding(term);
            if(findTerm != nullptr) term->match(*findTerm);
        }
        _terms.push_back(term);
        while((_currentToken = _scanner.nextToken()) == ',' ||  _currentToken=='='|| _currentToken == ';') {
            if (_currentToken == '=') {
                isCOMMA = 0;
                Node * left = new Node(TERM, _terms.back(), nullptr, nullptr);
                _terms.push_back(createTerm());
                Node * right = new Node(TERM, _terms.back(), nullptr, nullptr);
                Node * root = new Node(EQUALITY, nullptr, left, right);
                _expressionTree = root;
            }
            else if(_currentToken == ','){
                isCOMMA = 1;
                Node * left = _expressionTree;
                matchings();
                Node * root = new Node(COMMA, nullptr, left, expressionTree());
                _expressionTree = root;
            }
            else if(_currentToken == ';'){
                isCOMMA = 0;
                _newStartIndex = _terms.size();
                Node * left = _expressionTree;
                matchings();
                Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
                _expressionTree = root;
            }
        }
    }
}

Term* Parser::finding(Term *term){
    for(int index = _newStartIndex; index < _terms.size() ; index++){
        if(_terms[index]->symbol() == term->symbol()){
            return _terms[index];
        }
        Struct * s = dynamic_cast<Struct*>(_terms[index]);
        if(s) {
            return findStruct(s,term);
        }
    }
    return nullptr;
}

Term* Parser::findStruct(Struct* s, Term* term){
    for(int i = 0; i < s->arity() ; i++){
        if(s->args(i)->symbol() == term->symbol()) return s->args(i);
        Struct * ss = dynamic_cast<Struct*>(s->args(i));
        if(ss) {
            return findStruct(ss,term);
        }
    }
  }

Node* Parser::expressionTree(){
    return _expressionTree;
}

void Parser::createTerms(){
    Term* term = createTerm();
    if(term!=nullptr)
    {
        _terms.push_back(term);
        while((_currentToken = _scanner.nextToken()) == ',') {
            _terms.push_back(createTerm());
        }
    }
}

vector<Term*>& Parser::getTerms(){
    return _terms;
}

vector<Term*> Parser::getArgs()
{
    Term* term = createTerm();
    vector<Term*> args = {};
    if(term){
      Variable* variable = dynamic_cast<Variable*>(term);
      if(variable != nullptr){
          for(int index = _newStartIndex; index < _terms.size(); index++){
              if(variable->symbol() == _terms[index]->symbol()) _terms[index]->match(*variable);
          }
      }
      args.push_back(term);
    }
    if((_currentToken == ']' || _currentToken == ')') && term == nullptr){
        return args;
    }
    while((_currentToken = _scanner.nextToken()) == ',') {
            args.push_back(createTerm());
    }
    return args;
}

