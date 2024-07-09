#include "treap.hpp"
#include <iostream>

using namespace std;

TreapNode* insert(TreapNode* treap, int k, int p)
{
    if(!treap)
    {
        return new TreapNode(k,p);
        
    }

    if(k < treap->key)
    {
        treap->left=insert(treap->left,k,p);
        if(treap->left->priority > treap->priority)
        {
            rotateRight(treap);
        }
    }
    else if (k > treap->key)
    {
        treap->right = insert(treap->right,k,p);
        if(treap->right->priority > treap->priority)
        {
            rotateLeft(treap);
        }
    }
    else
    {
        /*Key is alredy in Treap*/
    }
    return treap;

}
TreapNode* remove(TreapNode* treap, int k)
{
    if(!treap)
    {
        return nullptr;
    }
        
    if(k < treap->key)
    {
        treap->left = remove(treap->left,k);
    }     
    else if(k > treap->key)
    {
        treap->right = remove(treap->right,k);
    }
    else 
    {
        if(!treap->left)
        {
            TreapNode* r = treap->right;
            delete treap; 
            treap = r;
        }
        else if(!treap->right)
        {
            TreapNode* l = treap->left;
            delete treap;
            treap = l;
        }
        else 
        {
            if(treap->left->priority > treap->right->priority)
            {
                rotateRight(treap);
                treap->right = remove(treap->right,k);
            }
            else 
            {
                rotateLeft(treap);
                treap->left = remove(treap->left,k);
            }
        }
    }
    return treap;
}

TreapNode* search(TreapNode* treap, int k)
{
    if(!treap)
    {
        return nullptr;
    }
    if(k == treap->key)
    {
        return treap;
    }
    else if (k < treap->key)
    {
        return search(treap->left,k);
    }
    else
    {
        return search(treap->right,k);
    }
}

pair<TreapNode*,TreapNode*> split(TreapNode* treap, int a)
{
    treap = insert(treap,a,INT_MAX);

    TreapNode* left = treap->left;
    TreapNode* right = treap-> right;

    delete treap;

    return {left, right};
}

TreapNode* merge(TreapNode* left,TreapNode* right)
{
    TreapNode* newNode = new TreapNode(INT_MAX,INT_MAX);
    newNode->left = left;
    newNode->right = right;

    TreapNode* mergedTreap = remove(newNode,INT_MAX);
    return mergedTreap;
}

int depth(TreapNode* treap)
{
    if(!treap)
    {
        return 0;
    }
    else
    {
        return max(depth(treap->left),depth(treap->right))+1;
    }
}

void rotateRight(TreapNode* &treap)
{
    TreapNode* l = treap->left;
    treap->left = l->right;
    l->right = treap;
    treap = l;
}

void rotateLeft(TreapNode* &treap)
{
    TreapNode* r = treap->right;
    treap->right = r->left;
    r->left = treap;
    treap = r;
}

void printTreap(TreapNode* root, int depth)
{
    if(!root)
    {
        return;
    }
    printTreap(root->right,depth+1);
    
    for(int i=0;i<depth;i++)
    {
        cout <<"       ";
    }
    
    cout << "(" << root->key <<", "<<root->priority <<")\n";

    printTreap(root->left,depth+1);
}

void freeTreap(TreapNode* root)
{
    if(root)
    {
        freeTreap(root->left);
        freeTreap(root->right);
        delete root;
    }
}