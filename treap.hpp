#ifndef TREAP_HPP
#define TREAP_HPP 

#include <iostream>
#include <random>
#include <limits>
#include <climits>
#include <utility>

using namespace std;

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
TreapNode* search(TreapNode* treap, int k);

pair<TreapNode*,TreapNode*> split(TreapNode* treap, int a);
TreapNode* merge(TreapNode*,TreapNode*);

int depth(TreapNode* treap);

void rotateRight(TreapNode* &treap);
void rotateLeft(TreapNode* &treap);

void printTreap(TreapNode* root,int depth=0);
void freeTreap(TreapNode* root);

#endif