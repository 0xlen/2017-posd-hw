#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    vector<Term *> args = {};
    List l(args);
    EXPECT_EQ("[]", l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
    Number number1(8128), number2(496);
    vector<Term *> args = {&number1, &number2};
    List l(args);
    EXPECT_EQ(string("[8128, 496]"), l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom atom1("terence_tao"), atom2("alan_mathison_turing");
    vector<Term *> args = {&atom1, &atom2};
    List l(args);
    EXPECT_EQ(string("[terence_tao, alan_mathison_turing]"), l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X"), Y("Y");
    vector<Term *> args = {&X, &Y};
    List l(args);
    EXPECT_EQ(string("[X, Y]"), l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Atom atom1("tom");
    Number number1(496);
    Variable variable1("X");
    Atom atom2("terence_tao");
    vector<Term *> args = {&number1, &variable1, &atom2};
    List l(args);
    ASSERT_FALSE(atom1.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number number1(8128);
    Number number2(496);
    Variable variable1("X");
    Atom atom1("terence_tao");
    vector<Term *> args = {&number2, &variable1, &atom1};
    List l(args);
    ASSERT_FALSE(number1.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Variable variable1("X");
    vector<Term *> v = {&variable1};
    Struct s(Atom("s"), v);
    Number number1(496);
    Atom atom1("terence_tao");
    vector<Term *> args = {&number1, &variable1, &atom1};
    List l(args);
    ASSERT_FALSE(s.match(l));
}


// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Number number1(496);
    Variable variable1("X");
    Atom atom1("terence_tao");
    vector<Term *> args = {&number1, &variable1, &atom1};
    List l(args);
    Variable variable2("Y");
    ASSERT_TRUE(variable2.match(l));
    ASSERT_TRUE(l.match(variable2));
    EXPECT_EQ(string("[496, X, terence_tao]"), variable2.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number number1(496);
    Variable variable1("X");
    Atom atom1("terence_tao");
    vector<Term *> args = {&number1, &variable1, &atom1};
    List l(args);
    ASSERT_TRUE(variable1.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number number1(496);
    Variable variable1("X");
    Atom atom1("terence_tao");
    vector<Term *> args = {&number1, &variable1, &atom1};
    List l1(args);
    ASSERT_TRUE(l1.match(l1));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number number1(496);
    Variable variable1("X");
    Variable variable2("Y");
    Atom atom1("terence_tao");
    vector<Term *> args1 = {&number1, &variable1, &atom1};
    vector<Term *> args2 = {&number1, &variable2, &atom1};
    List l1(args1);
    List l2(args2);
    ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number number1(496);
    Number number2(8128);
    Variable variable1("X");
    Atom atom1("terence_tao");
    vector<Term *> args1 = {&number1, &variable1, &atom1};
    vector<Term *> args2 = {&number1, &number2, &atom1};
    List l1(args1);
    List l2(args2);
    ASSERT_TRUE(l1.match(l2));
    EXPECT_EQ("8128", variable1.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Variable Y("Y");
    Variable X("X");
    Atom atom1("alan_mathison_turing");
    X.match(atom1);
    Number number1(496);
    Atom atom2("terence_tao");
    vector<Term *> args = {&number1, &X, &atom2};
    List l1(args);
    Y.match(l1);
    EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
    EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first");
    vector<Term *> args1 = {&f};
    List l1(args1);
    Atom s("second"), t("third");
    vector<Term *> args2 = {&l1, &s, &t};
    List l2(args2);
    EXPECT_EQ(string("[first]"), l2.head()->value());
    EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
    EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    vector<Term *> args = {};
    List l(args);
    try{
        l.head();
    }catch(string s){
        EXPECT_EQ(string("Accessing head in an empty list"), s);
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    vector<Term *> args = {};
    List l(args);
    try{
        l.tail();
    }catch(string s){
        EXPECT_EQ(string("Accessing tail in an empty list"), s);
    }
}



#endif
