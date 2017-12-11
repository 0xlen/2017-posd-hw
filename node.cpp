#include "include/node.h"


Node::Node(Operators op) {
    payload = op;
    term = 0;
    left = 0;
    right = 0;
}

Node::Node(Operators op, Term *t, Node *l, Node *r) {
    payload = op;
    term = t;
    left = l;
    right = r;
}

bool Node::evaluate() {
    if(payload == EQUALITY) {
        return left->term->match(*(right->term));
    }

    else if (payload == COMMA) {
        bool l = left->evaluate();
        bool r = right->evaluate();

        return l && r;
    }
    else if (payload == SEMICOLON) {
        bool l = left->evaluate();
        bool r = right->evaluate();

        return l || r ;
    }

    return false;
}
