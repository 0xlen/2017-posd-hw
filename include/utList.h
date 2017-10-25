#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

using std::string;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    List list;

    ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
    Number number1(496), number2(8128);
    vector<Term *> args = {&number1, &number2};
    List list(args);

    ASSERT_EQ("[496, 8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom terenceTao("terence_tao");
    Atom alanMathisonTuring("alan_mathison_turing");
    vector<Term *> args = {&terenceTao, &alanMathisonTuring};
    List list(args);

    ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X");
    Variable Y("Y");
    vector<Term *> args = {&X, &Y};
    List list(args);

    ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Atom tom("tom");

    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");
    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number leftNumber(8128);

    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");
    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    ASSERT_FALSE(leftNumber.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");

    vector<Term *> sv = {&X};
    Struct s(Atom("s"), sv);

    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    ASSERT_FALSE(s.match(list));

}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");

    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    Variable Y("Y");

    ASSERT_TRUE(Y.match(list));
    ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");

    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    Variable Y("Y");

    ASSERT_TRUE(Y.match(list));
    ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number number(496);
    Variable X("X");
    Atom terenceTao("terence_tao");

    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number number(496);
    Variable X("X");
    Variable Y("Y");
    Atom terenceTao("terence_tao");

    vector<Term *> args1 = {&number, &X, &terenceTao},
        args2 = {&number, &Y, &terenceTao};

    List list1(args1), list2(args2);

    ASSERT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number number1(496), number2(8128);
    Variable X("X");
    Atom terenceTao("terence_tao");

    vector<Term *> args1 = {&number1, &X, &terenceTao},
        args2 = {&number1, &number2, &terenceTao};

    List list1(args1), list2(args2);

    ASSERT_TRUE(list1.match(list2));
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Number number(496);
    Variable X("X"), Y("Y");
    Atom terenceTao("terence_tao"), alanMathisonTuring("alan_mathison_turing");

    vector<Term *> args = {&number, &X, &terenceTao};
    List list(args);

    ASSERT_TRUE(Y.match(list));
    ASSERT_TRUE(X.match(alanMathisonTuring));
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
    ASSERT_EQ("alan_mathison_turing", X.value());
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
    Atom f("first"), s("second"), t("third");
    vector<Term *> args1 = {&f};
    List list1(args1);
    vector<Term *> args2 = {&list1, &s, &t};
    List list2(args2);

    EXPECT_EQ(string("[first]"), list2.head()->symbol());
    EXPECT_EQ(string("[second, third]"), list2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List list(args);

    EXPECT_EQ(string("third"), list.tail()->tail()->head()->value());
    EXPECT_EQ(string("[]"), list.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    List list;
    try {
        list.head();
    } catch (string errorMessage) {
        EXPECT_EQ("Accessing head in an empty list", errorMessage);
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    List list;
    try {
        list.tail();
    } catch (string errorMessage) {
        EXPECT_EQ("Accessing tail in an empty list", errorMessage);
    }
}

#endif
