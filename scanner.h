#ifndef SCANNER_H
#define SCANNER_H

#include <algorithm>
#include <string>
#include <vector>

const int NONE = -1; // no tokenValue

// tokens return by the scanner
const int EOS = '\0';
const int NUMBER = 256;
const int ATOM = 257;
const int ATOMSC = 258;
const int VAR = 259;
const int LIST = 260;

using std::pair;

using std::string;
using std::vector;

extern vector<pair<string, int>> symtable;
extern bool isSpecialCh(char c);
extern bool symbolExist(string s, int & val);



class Scanner {
    public:
        Scanner (string in=""):buffer(in), pos(0), _tokenValue(NONE){}
        void setInput(string in);
        int nextToken();
        int tokenValue() const;
        int skipLeadingWhiteSpace();
        int position() const;
        char currentChar();
        // extractX: extract X and set position right after X
        int extractNumber();
        string extractAtom();
        string extractAtomSC();
        string extractVar();
        char extractChar();
        char watchString(int index);
    private:
        string buffer;
        int pos;
        int _tokenValue;


    private:
        // case-based populating symtable and setting _tokenValue
        template <int TokenType>
        void processToken(string const & s) {
            int val = -1;
            if (symbolExist(s,val)) {
                _tokenValue = val;
            } else {
            symtable.push_back(pair<string, int>(s,TokenType));
            _tokenValue = symtable.size()-1; // index to symtable
            }
        }
};


#endif
