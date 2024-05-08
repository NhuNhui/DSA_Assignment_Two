#include<bits/stdc++.h>
using namespace std;

//AVL ==========================================================
class Node
{
	public:
        pair<int,int> infor; //id - result
        Node *left;
        Node *right;
        int height;
};
int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
Node* newNode(pair<int,int> infor)
{
	Node* node = new Node();
	node->infor = infor;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}

Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),height(y->right)) + 1;
	x->height = max(height(x->left),height(x->right)) + 1;

	// Return new root
	return x;
}

Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1;

	// Return new root
	return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, pair<int,int> infor)
{
	/* 1. Perform the normal BST rotation */
	if (node == NULL)
		return(newNode(infor));

	if (infor.second < node->infor.second)
		node->left = insert(node->left, infor);
	else 
		node->right = insert(node->right, infor);

	// Cập nhật lại độ cao của cây
	node->height = 1 + max(height(node->left),height(node->right));

	// cân bằng lại cây
	int balance = getBalance(node);

	// Left Left Case
	if (balance > 1 && infor.second < node->left->infor.second)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && infor.second > node->right->infor.second)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && infor.second > node->left->infor.second)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && infor.second < node->right->infor.second)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

// Delete =============================================================
Node * minValueNode(Node* node)
{
	Node* current = node;
	while (current->left != NULL)
		current = current->left;

	return current;
}
// check sau =======================================================
Node* deleteNode(Node* &root, pair<int,int> infor)
{
	if (root == NULL)
		return root;

	if (infor.first < root->infor.first)
		root->left = deleteNode(root->left, infor);

	else if(infor.first > root->infor.first)
		root->right = deleteNode(root->right, infor);

	// if infor is same as root's infor, then
	// This is the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) ||
			(root->right == NULL) )
		{
			Node *temp = root->left ? root->left : root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
			*root = *temp; // Copy the contents of
						// the non-empty child
			free(temp);
		}
		else
		{
			Node* temp = minValueNode(root->right);
			root->infor = temp->infor;
			root->right = deleteNode(root->right,temp->infor);
		}
	}

	// If the tree had only one node
	// then return
	if (root == NULL)
	return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root);
	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void print(Node *root)
{
    if(root == NULL)    return;
    queue<Node*> qu;
    qu.push(root);
    while(!qu.empty()) {
        vector<pair<int,int>> v;
        int length = qu.size();
        while(length > 0) {
            Node *t = qu.front();
            v.push_back(qu.front()->infor);
            qu.pop();
            if(t->left!=NULL)   qu.push(t->left);
            if(t->right!=NULL)  qu.push(t->right);
            length--;
        }
        for(int i=0;i<int(v.size());i++) {
			cout<<v[i].first<<"-"<<v[i].second<<"\n";
		}
		v.clear();
    }
}

int main() {
	Node *root = NULL;

	root = insert(root,{3,5});
	root = insert(root,{2,4});
	root = insert(root,{9,10});
	root = insert(root,{3,6});
	root = insert(root,{3,8});
	root = insert(root,{2,1});
	root = insert(root,{9,2});
	root = insert(root,{3,7});
	root = deleteNode(root,{2,4});
	cout << "Preorder traversal of the "
			"constructed AVL tree is \n";
	print(root);
	return 0;
}