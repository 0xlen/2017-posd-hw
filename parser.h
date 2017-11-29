#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "atom.h"
#include "variable.h"
#include "scanner.h"
#include "struct.h"
#include "term.h"
#include "list.h"
#include "node.h"

using std::string;

class Parser{
    public:
        Parser(Scanner scanner) : _scanner(scanner){}
        Term* createTerm();
        vector<Term*> getArgs();
        void matchings();
        Term* finding(Term*);
        Term* findStruct(Struct*,Term*);
        Node* expressionTree();
        void createTerms();
        vector<Term*> &getTerms();
    private:
        Scanner _scanner;
        int _currentToken;
        Node * _expressionTree;
        int isCOMMA = 0;
        vector<Term *> _terms;
        int _newStartIndex = 0;
};
#endif
