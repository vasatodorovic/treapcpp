#ifndef TREAP_HPP
#define TREAP_HPP 

#include <iostream>
#include <random>
#include <limits>

struct TreapNode {

    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;


    TreapNode(){}
    TreapNode(int k,int p):key(k),priority(p),left(nullptr),right(nullptr){}
};

TreapNode* insert(TreapNode* treap, int k, int p);
TreapNode* remove(TreapNode* treap, int k);

void rotateRight(TreapNode* &treap);
void rotateLeft(TreapNode* &treap);

void printTreap(TreapNode* root,int depth=0);

#endif