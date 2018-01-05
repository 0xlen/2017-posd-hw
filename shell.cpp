#include <iostream>
#include <string>

#include "atom.h"
#include "variable.h"
#include "exp.h"
#include "parser.h"
#include "list.h"
#include "struct.h"

using namespace std;

int main() {
    string::size_type position;
    string str, result =  "";

    cout << "?-";
    while (str != "halt") {

        getline(cin, str, '\n');
        position = str.find(".");

        if (str != " " || str != "\n") {
            result += str;
        }

        if (position != str.npos) {
            Scanner s(result);
            Parser p(s);

            try{
                p.buildExpression();
                string result = getResult(p.getExpressionTree());
                cout << result << "\n\n";
            } catch (std::string & msg) {
                cout << msg << "\n";
            }

            result = "";
        }

        if (result == "") {
            cout << "?-";
        } else if (result != "halt") {
            cout << "|  ";
        }
    }

}
