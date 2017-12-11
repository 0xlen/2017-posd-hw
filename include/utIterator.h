#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "number.h"
#include "iterator.h"

#include <vector>
using std::vector;

TEST(iterator, first)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term *> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator)
{
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), {&X, &two});
    Struct s(Atom("s"), {&one, &t, &Y});
    Iterator<Term *> *it = s.createIterator();
    it->first();
    it->next();
    Struct *s2 = dynamic_cast<Struct *>(it->currentItem());
    Iterator<Term *> *it2 = s2->createIterator();
    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList)
{
    // Number one(1);
    // Variable X("X");
    // Variable Y("Y");
    // Number two(2);
    // Struct t(Atom("t"), {&X, &two});
    // List l({&one, &t, &Y});
    // Iterator<Term *> *itList = l.createIterator();
    // itList->first();
    // ASSERT_EQ("1", itList->currentItem()->symbol());
    // ASSERT_FALSE(itList->isDone());
    // itList->next();
    // ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    // ASSERT_FALSE(itList->isDone());
    // itList->next();
    // ASSERT_EQ("Y", itList->currentItem()->symbol());
    // itList->next();
    // ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator)
{
    Number one(1);
    Iterator<Term *> *nullIterator = one.createIterator();
    nullIterator->first();
    ASSERT_TRUE(nullIterator->isDone());
}

TEST(iterator, DFS_struct_1D)
{
    Number n1(1);
    Atom a1("a");
    vector<Term *> v = {&n1, &a1};
    Struct s(Atom("s"), v);

    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, DFS_struct_3D)
{
    // s2(s(1,a),s1(s(1,a)))
    Number n1(1);
    Atom a1("a");
    vector<Term *> v = {&n1, &a1};
    Struct s(Atom("s"), v);
    vector<Term *> v1 = {&s};
    Struct s1(Atom("s1"), v1);
    vector<Term *> v2 = {&s, &s1};
    Struct s2(Atom("s2"), v2);

    Iterator<Term *> *it = s2.createDFSIterator();
    it->first();
    ASSERT_EQ("s(1, a)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("s1(s(1, a))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("s(1, a)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, BFS_struct_1D)
{
    Number n1(1);
    Atom a1("a");
    vector<Term *> v = {&n1, &a1};
    Struct s(Atom("s"), v);

    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, BFS_struct_3D)
{
    // s2(s(1,a),s1(s(1,a)))
    Number n1(1);
    Atom a1("a");
    vector<Term *> v = {&n1, &a1};
    Struct s(Atom("s"), v);
    vector<Term *> v1 = {&s};
    Struct s1(Atom("s1"), v1);
    vector<Term *> v2 = {&s, &s1};
    Struct s2(Atom("s2"), v2);

    Iterator<Term *> *it = s2.createBFSIterator();
    it->first();
    ASSERT_EQ("s(1, a)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("s1(s(1, a))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("s(1, a)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("a", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

#endif
