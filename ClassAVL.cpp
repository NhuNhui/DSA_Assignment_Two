#include<bits/stdc++.h>
using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }

    Node *rotateRight(Node *t) {
        Node *x = t->pLeft;
        Node *temp = x->pRight;
        x->pRight = t;
        t->pLeft = temp;
        
        return x;
    }
    Node *rotateLeft(Node *t) {
        Node *x = t->pRight;
        Node *temp = x->pLeft;
        x->pLeft = t;
        t->pRight = temp;
        return x;
    }
    Node* insert(Node *root,const int &value) {
        if(root == NULL) {
            return new Node(value);
        }
        if(value < root->data) {
            root->pLeft = insert(root->pLeft,value);
        }
        else if(value >= root->data) {
            root->pRight = insert(root->pRight,value);
        }
        
        int left = getHeightRec(root->pLeft);
        int right = getHeightRec(root->pRight);
        BalanceValue balanceFactor;
        if(left - right > 1)    balanceFactor = LH;
        else if(right - left > 1) balanceFactor = RH;
        else    balanceFactor = EH;
    
        
        if(balanceFactor == LH && value < root->pLeft->data) {
            return rotateRight(root);
        }
        if(balanceFactor == RH && value >= root->pRight->data){
            return rotateLeft(root);
        }
        if(balanceFactor == LH && value > root->pLeft->data) {
            root->pLeft = rotateLeft(root->pLeft);
            return rotateRight(root);
        }
        if(balanceFactor == RH && value <= root->pRight->data) {
            root->pRight = rotateRight(root->pRight);
            return rotateLeft(root);
        }
        return root;
    }
    void insert(const int &value)
    {
        this->root = insert(this->root,value);
    }

    class Node
    {
    private:
        int data;
        Node *pLeft, *pRight;
        friend class AVLTree;

    public:
        Node(int value) : data(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};
