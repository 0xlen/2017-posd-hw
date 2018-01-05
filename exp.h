#ifndef EXP_H
#define EXP_H

#include "atom.h"



#include <string>
#include <iostream>
#include <deque>

using namespace std;

class Exp {
    public:
        virtual bool evaluate() = 0;
        virtual string result(){}
};

string getResult(Exp *e) {
    string result = "";

    if (!e->evaluate()) {
        result = "false.";
    } else {
        result = e->result();

        if (result == "") {
            result = "true.";
        } else {
            result += ".";
        }
    }

    return result;
}

class MatchExp : public Exp {
    public:
        MatchExp(Term* left, Term* right): _left(left), _right(right){
        }

        bool evaluate(){
            return _left->match(*_right);
        }

        string result(){

            string res = "";
            if (_left->symbol() == _right->symbol()) {
                return "";
            }

            Variable* isLeftVar = dynamic_cast<Variable*>(_left);
            Variable* isRighttVar = dynamic_cast<Variable*>(_right);

            if (isLeftVar && isRighttVar) {
                return _left->symbol() + " = " + _right->symbol();
            }

            if (isLeftVar) {
                return _left->symbol() + " = " + _left->value();
            }

            if (isRighttVar) {
                return _right->symbol() + " = " + _right->value();
            }

            return _left->symbol() + " = " + _right->symbol();
        }

    public:
        Term* _left;
        Term* _right;
};

class ConjExp : public Exp {
    public:
        ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

        }

        bool evaluate() {
            bool eval = _left->evaluate() && _right->evaluate();
            _boolEval = eval;

            return eval;
        }


        string result(){
            string res = _left->result();

            std::size_t found = res.find(_right->result());
            if (_left->result() != _right->result()) {
                if (found !=std::string::npos) {
                } else if (_left->result() == "") {
                    res += _right->result();
                } else if (_right->result() != "") {
                    res += ", " + _right->result();
                }
            }

            return res;
        }

    private:
        bool _boolEval;
        Exp * _left;
        Exp * _right;
};

class DisjExp : public Exp {
    public:
        DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

        }

        bool evaluate() {
            _leftEval = _left->evaluate();
            _rightEval = _right->evaluate();

            return _leftEval || _rightEval;
        }

        string result(){
            string res = "";

            if (_leftEval) res += _left->result();
            if (_rightEval && (_left->result() !=_right->result())) {
                if ( _right->result() == "") {
                    res += "; true";
                } else {
                    if ( !_leftEval) {
                        res += _right->result();
                    } else {
                        res += "; " + _right->result();
                    }
                }
            }


            return res;
        }

    private:
        bool _leftEval;
        bool _rightEval;
        Exp * _left;
        Exp * _right;
};
#endif
