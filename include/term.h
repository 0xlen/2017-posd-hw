#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term {

    public:
        virtual string symbol();
        virtual string value();
        bool match();
};

#endif
