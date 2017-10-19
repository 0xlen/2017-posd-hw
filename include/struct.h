#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>
#include "atom.h"
#include "term.h"

using namespace std;

class Struct : public Term
{
    public:
        Struct(Atom const & name, std::vector<Term *> args) {
            _name = name;
            _args = args;
        }

        Atom const & name() {
            return _name;
        }

        Term *args(int index) {
            return _args[index];
        }

        string symbol() const {
            string ret = _name.symbol() + "(";
            for(int i = 0; i < _args.size() - 1 ; i++){
                ret += _args[i]-> symbol() + ", ";
            }
            ret += _args[_args.size()-1]-> symbol() + ")";
            return  ret;
        }

        bool match(Term &term) {
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

        string value() const {
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

    private:
        Atom _name;
        vector<Term *> _args;
};

#endif
