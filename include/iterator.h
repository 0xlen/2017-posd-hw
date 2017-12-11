#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include "struct.h"
#include "list.h"
#include "node.h"
#include <stack>
#include <queue>

using std::queue;
using std::stack;

class Struct;

template <class T>
class Iterator
{
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual Term *currentItem() const = 0;
        virtual bool isDone() const = 0;
};

template <class T>
class NullIterator : public Iterator<T>
{
    public:
        NullIterator(Term *n) {}
        void first() {}
        void next() {}
        Term *currentItem() const
        {
            return nullptr;
        }
        bool isDone() const
        {
            return true;
        }
};

template <class T>
class StructIterator : public Iterator<T>
{
    public:
        StructIterator(Struct *s) {
            _index = 0;
            _s = s;
        }
        void first()
        {
            _index = 0;
        }

        Term *currentItem() const
        {
            return _s->args(_index);
        }

        bool isDone() const
        {
            return _index >= _s->arity();
        }

        void next()
        {
            _index++;
        }

    private:
        int _index;
        Struct *_s;
};

template <class T>
class ListIterator : public Iterator<T>
{
    public:
        ListIterator(List *list) : _index(0), _list(list) {}

        void first()
        {
            _index = 0;
        }

        Term *currentItem() const
        {
            return _list->args(_index);
        }

        bool isDone() const
        {
            return _index >= _list->arity();
        }

        void next()
        {
            _index++;
        }

    private:
        int _index;
        List *_list;
};

template <class T>
class DFSIterator : public Iterator<T>
{
    public:
        DFSIterator(T t) : _t(t) {}

        void first()
        {
            _nowT = _t;
            while (!_ts.empty())
            {
                _ts.pop();
            }

            for (int i = (int)_nowT->arity() - 1; i >= 0; i--)
            {
                _ts.push(_nowT->args(i));
            }

            if (!_ts.empty())
            {
                next();
            }
        }

        Term *currentItem() const
        {
            return _nowT;
        }

        bool isDone() const
        {
            return _ts.empty();
        }

        void next()
        {
            if (!isDone())
            {
                _nowT = _ts.top();
                _ts.pop();
                for (int i = (int)_nowT->arity() - 1; i >= 0; i--)
                {
                    _ts.push(_nowT->args(i));
                }
            }
        }

    private:
        T _t;
        stack<T> _ts;
        T _nowT;
};

template <class T>
class BFSIterator : public Iterator<T>
{
    public:
        BFSIterator(T t) : _t(t) {}

        void first()
        {
            _nowT = _t;
            while (!_ts.empty())
            {
                _ts.pop();
            }

            for (int i = 0; i < (int)_nowT->arity(); i++)
            {
                _ts.push(_nowT->args(i));
            }

            if (!_ts.empty())
            {
                next();
            }
        }

        Term *currentItem() const
        {
            return _nowT;
        }

        bool isDone() const
        {
            return _ts.empty();
        }

        void next()
        {
            if (!isDone())
            {
                _nowT = _ts.front();
                _ts.pop();
                for (int i = 0; i < (int)_nowT->arity(); i++)
                {
                    _ts.push(_nowT->args(i));
                }
            }
        }

    private:
        T _t;
        queue<T> _ts;
        T _nowT;
};
#endif
