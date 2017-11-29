#ifndef UTTERM_H
#define UTTERM_H

#include "atom.h"
#include "number.h"
#include "variable.h"
#include <string>
#include "term.h"
#include "struct.h"

//test Number.value()
TEST (Number,ctor) {
    Number number1(25);
    ASSERT_EQ("25",number1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number number1(25);
    ASSERT_EQ("25", number1.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number number1(25);
    Number number2(25);
    ASSERT_TRUE(number1.match(number2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number number1(25);
    Number number2(0);
    ASSERT_FALSE(number1.match(number2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number number1(25);
    Atom atom1("tom");
    ASSERT_FALSE(number1.match(atom1));
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number number1(25);
    Variable variable1("X");
    ASSERT_TRUE(number1.match(variable1));
    ASSERT_EQ(number1.value(), variable1.value());
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom atom1("tom");
    Number number1(25);
    ASSERT_FALSE(atom1.match(number1));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom atom1("tom");
    Variable variable1("X");
    ASSERT_TRUE(atom1.match(variable1));
    ASSERT_EQ(variable1.value(), atom1.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Variable variable1("X");
    Atom atom1("tom");
    variable1.match(atom1);
    ASSERT_TRUE(atom1.match(variable1));
    ASSERT_EQ(variable1.value(), atom1.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable variable1("X");
    Atom atom1("jerry");
    Atom atom2("tom");
    variable1.match(atom1);
    ASSERT_FALSE(atom2.match(variable1));
    ASSERT_EQ(variable1.value(), atom1.value());
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable variable1("X");
    Number number1(5);
    ASSERT_TRUE(variable1.match(number1));
    ASSERT_EQ(variable1.value(), number1.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable variable1("X");
    Number number1(25);
    Number number2(100);
    variable1.match(number1);
    ASSERT_FALSE(variable1.match(number2));
    ASSERT_EQ(variable1.value(), number1.value());
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable variable1("X");
    Atom atom1("tom");
    Number number1(25);
    variable1.match(atom1);
    ASSERT_FALSE(variable1.match(number1));
    ASSERT_EQ(variable1.value(), atom1.value());
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Atom atom1("tom");
    Variable variable1("X");
    Number number1(25);
    atom1.match(variable1);
    ASSERT_FALSE(number1.match(variable1));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Variable variable1("X");
    Atom atom1("tom");
    variable1.match(atom1);
    ASSERT_TRUE(variable1.match(atom1));
    ASSERT_EQ(variable1.value(), atom1.value());
}

#endif
