#include "variable.h"
#include "atom.h"
#include "number.h"

#ifndef UTTERM_H
#define UTTERM_H

//test Number.value()
TEST (Number, ctor) {
    Number number(1);

    ASSERT_EQ("1", number.value()); 
}
//test Number.symbol()
TEST (Number, symbol) {
    Number number(12);

    ASSERT_EQ("12", number.value()); 
}
//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
    Number numberA(25);
    Number numberB(25);

    ASSERT_TRUE(numberA.match(numberB));
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
    Number numberA(25);
    Number numberB(0);

    ASSERT_FALSE(numberA.match(numberB));
}
//?- 25 = tom.
// false.
TEST (Number, matchFailureDiffConstant) {
    Number number(25);
    Atom tom("tom");

    ASSERT_FALSE(number.match(tom));
}
//?- 25 = X.
// true.
TEST (Number, matchSuccessToVar) {
    Number number(25);
    Variable x("X");

    ASSERT_TRUE(number.match(x));
}

//?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number number(25);

    ASSERT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Variable x("X");

    ASSERT_TRUE(x.match(tom));
}

// ?- X = tom, tom = X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Variable x("X");
    Atom tom("tom");

    ASSERT_TRUE(x.match(tom));
    ASSERT_TRUE(tom.match(x));
}

// ?- X = jerry, tom = X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable x("X");
    Atom tom("tom");
    Atom jerry("jerry");

    ASSERT_TRUE(x.match(jerry));
    ASSERT_FALSE(tom.match(x));
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
    Variable x("X");
    Number number(5);

    ASSERT_TRUE(x.match(number));
}

// ?- X = 25, X = 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
    Number numberA(25);
    Number numberB(100);
    Variable x("X");

    ASSERT_TRUE(x.match(numberA));
    ASSERT_FALSE(x.match(numberB));
}

// ?- X = tom, X = 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
    Number number(25);
    Atom tom("tom");
    Variable x("X");

    ASSERT_TRUE(x.match(tom));
    ASSERT_FALSE(x.match(number));
}
//?- tom = X, 25 = X.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
    Number number(25);
    Atom tom("tom");
    Variable x("X");

    ASSERT_TRUE(tom.match(x));
    ASSERT_FALSE(number.match(x));
}
//?- X = tom, X = tom.
// true.
TEST(Variable, reAssignTheSameAtom){
    Atom tom("tom");
    Variable x("X");

    ASSERT_TRUE(x.match(tom));
    ASSERT_TRUE(x.match(tom));
}
#endif
