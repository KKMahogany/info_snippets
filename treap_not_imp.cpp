/*
 * Simple (non-implicit) treap that supports the basic SBBST operations.
 */
#include <algorithm>
#include <iostream>
#include <cassert>
 
using namespace std;
 
struct node {
    node *lc, *rc;
    int v, p;
};
 
node* newNode(int v) {
    node* n = new node;
    n->v = v;
    n->p = rand();
    n->lc = NULL;
    n->rc = NULL;
    return n;
}
 
void printTree(node* cur) {
    if(!cur) {
        return;
    }
    printTree(cur->lc);
    cout << cur->v << " ";
    printTree(cur->rc);
}
 
node* merge(node* left, node *right) {
    // Base case: one of them is the empty treap
    if(!left || !right) {
        return left ? left : right;
    }
 
    // The node with higher priority becomes the root.
    if(left->p > right->p) {
        left->rc = merge(left->rc, right);
        return left;
    } else {
        right->lc = merge(left, right->lc);
        return right;
    }
}

// Splits a treap into two. The left treap contains everything
// strictly less than value, the right treap contains everything
// greater than or equal to value.
void split_value(node* cur, int value, node *&lSplit, node *&rSplit) {
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
}
 
node *ROOT = NULL;
 
// Insert a value into the treap with a random priority.
void insert(node* &root, int index, int value) {
    auto* n = newNode(value);
    node *l = NULL, *r = NULL;
    split_value(root, index, l, r);
    l = merge(l, n);
    root = merge(l, r);
}

// TODO: Show how to do delete
