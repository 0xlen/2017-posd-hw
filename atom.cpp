#include "include/atom.h"
#include "include/variable.h"
#include "include/number.h"

bool Atom::match(Atom &atom){
    return false;
}

bool Atom::match(Number &number){
    return false;
}

bool Atom::match(Variable &variable){
    return variable.match(*this);
}
