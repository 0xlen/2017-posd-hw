#include "scanner.h"
#include <iostream>
void Scanner::setInput(string in){
    buffer = in;
}

int Scanner::nextToken(){
    if (skipLeadingWhiteSpace() >= buffer.length())
        return EOS;
    else if (isdigit(currentChar())) {
        _tokenValue = extractNumber();
        return NUMBER;
    }  else if (islower(currentChar())) {
        string s = extractAtom();
        processToken<ATOM>(s);
        return ATOM;
    } else if (isSpecialCh(currentChar())) {
        string s = extractAtomSC();
        processToken<ATOMSC>(s);
        return ATOMSC;
    } else if (isupper(currentChar()) || currentChar() == '_') {
        string s = extractVar();
        processToken<VAR>(s);
        return VAR;
    } else {
        _tokenValue = NONE;
        return extractChar();
    }
}

int Scanner::tokenValue() const {
    return _tokenValue;
}

int Scanner::skipLeadingWhiteSpace(){
    for (; (buffer[pos] == ' ' || buffer[pos] == '\t') && pos<buffer.length(); ++pos);
    return position();
}

int Scanner::position() const {
    return pos;
}

char Scanner::currentChar(){
    return buffer[pos];
}

int Scanner::extractNumber(){
    int posBegin = position();
    for (;isdigit(buffer[pos]); ++pos);
    return stoi(buffer.substr(posBegin, pos-posBegin));
}

string Scanner::extractAtom(){
    int posBegin = position();
    for (;isalnum(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

string Scanner::extractAtomSC(){
    int posBegin = position();
    for (;isSpecialCh(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

string Scanner::extractVar(){
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

char Scanner::extractChar(){
    return buffer[pos++];
}

vector<pair<string, int>> symtable;

bool isSpecialCh(char c) {
    return c == '+'
    // || c == '=' // ... the matching operator
    || c == '-'|| c == '*'|| c == '/'
    || c == '<'|| c == '>'|| c == '.'
    || c == '&'|| c == '\\'|| c == '~'
    || c == '^'|| c == '$'|| c == '#'
    || c == '@'|| c == '?'|| c == ':';
}

bool symbolExist(string s, int & val) {
    bool found = false;
    val = -1;
    vector<pair<string, int>>::iterator it = find_if(symtable.begin(), symtable.end(), [s](pair<string, int> ele) {
        return ele.first == s;
    });

    found = symtable.end() != it;
    if (found)
    val = it - symtable.begin();

    return found;
}

char Scanner::watchString(int index){
    return buffer[index];
}
