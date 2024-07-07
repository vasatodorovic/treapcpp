#include "treap.hpp"

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
    else 
    {
        treap->right = insert(treap->right,k,p);
        if(treap->right->priority > treap->priority)
        {
            rotateLeft(treap);
        }
    }

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