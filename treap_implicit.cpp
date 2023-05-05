#include <algorithm>
#include <iostream>
#include <cassert>
 
using namespace std;
 
struct node {
    node *lc, *rc;
    // v = value
    // p = priority
    // sz = size of your subtree
    int v, p, sz;
 
};
 
// Convenience function for getting the size of a treap,
// treating NULL as a treap of size 0.
int sz(node* n) {
    return n ? n->sz : 0;
}
 
// Recalculate the size of a node's subtree (or do
// nothing if it is the empty treap).
//
// Needs to be called whenever (and only when)
// you change a node's lc or rc.
void fix(node* n) {
    if(n) {
        n->sz = sz(n->lc) + sz(n->rc) + 1;
    }
}
 
node* newNode(int v) {
    node* n = new node;
    n->v = v;
    n->sz = 1;
    n->p = rand();
    n->lc = NULL;
    n->rc = NULL;
    return n;
}
 
void _printTree(node* cur) {
    if(!cur) {
        return;
    }
    _printTree(cur->lc);
    cout << cur->v << " ";
    _printTree(cur->rc);
}

// Simple debugging utility for printing out the whole tree
void printTree(node* cur) {
    _printTree(cur);
    cout << "\n";
}
 
node* merge(node* left, node *right) {
    // Base case: one of them is the empty treap
    if(!left || !right) {
        return left ? left : right;
    }
 
    // The node with higher priority becomes the root.
    if(left->p > right->p) {
        left->rc = merge(left->rc, right);
        fix(left);
        return left;
    } else {
        right->lc = merge(left, right->lc);
        fix(right);
        return right;
    }
}

// Splits a treap into two. The left treap contains everything
// at most (but not including) value, the right treap contains
// everything greater than or equal to value.
void split_value(node* cur, int value, node* &lSplit, node* &rSplit) {
    if(!cur) {
        // Splitting the empty treap gives two empty treaps
        lSplit = rSplit = NULL;
        return;
    }
    if(value <= cur->v) {
        split_value(cur->lc, value, lSplit, cur->lc);
        rSplit = cur;
    } else {
        split_value(cur->rc, value, cur->rc , rSplit);
        lSplit = cur;
    }
    fix(cur);
}
 
// Splits a treap into two. The left treap contains the
// index-th smallest elements, the right treap contains
// the remaining (N-index)-th elements.
void split(node* cur, int index, node* &lSplit, node* &rSplit) {
    if(!cur) {
        // Splitting the empty treap gives two empty treaps
        lSplit = rSplit = NULL;
        return;
    }
    if(index <= sz(cur->lc)) {
        split(cur->lc, index, lSplit, cur->lc);
        rSplit = cur;
    } else {
        split(cur->rc, index-sz(cur->lc)-1, cur->rc , rSplit);
        lSplit = cur;
    }
    fix(cur);
}

// Insert value at index (shifting everything after it), giving
// it a random priority.
void insert(node* &root, int index, int value) {
    auto* n = newNode(value);
    node *l = NULL, *r = NULL;
    split(root, index, l, r);
    l = merge(l, n);
    root = merge(l, r);
}
