#include "classes.h"
Node::Node()
{
	right = left = NULL;
	x = 0;
	y = 0;
	data = 0;
}
AVLNode::AVLNode()
{
	right = left = NULL;
	x = 0;
	y = 0;
	data = 0;
}
AVL::AVL()
{
	root = NULL;
	key = 0;
}
AVL::~AVL()
{
	delete root;
}
BST::BST()
{
	Root = NULL;
}
bool AVL::insert(int data, int& circX, int& circY, int& textX, int& textY, int& key)
{
	key = data % 10;
	AVLNode* newNode = new AVLNode;
	newNode->data = key;
	newNode->left = NULL;
	newNode->right = NULL;
	circX = 550;
	circY = 100;
	textX = 560;
	textY = 105;
	if (root == NULL)
	{
		root = newNode;
		newNode->tree.Insert(data, circX, circY, textX, textY);
		newNode->x = circX;
		newNode->y = circY;
		newNode->tx = textX;
		newNode->ty = textY;
	}
	else
	{
		AVLNode* node = root;
		while (1)
		{
			if (key < node->data)
			{
				if (node->left != NULL)
				{
					node = node->left;
					circX = circX - 50;
					circY = circY + 50;
					textX = textX - 50;
					textY = textY + 50;
				}
				else
				{
					circX = circX - 50;
					circY = circY + 50;
					textX = textX - 50;
					textY = textY + 50;
					node->left = newNode;
					node->left->tree.Insert(data, circX, circY, textX, textY);
					newNode->x = circX;
					newNode->y = circY;
					newNode->tx = textX;
					newNode->ty = textY;
					break;
				}
			}
			else if (key > node->data)
			{
				if (node->right != NULL)
				{
					node = node->right;
					circX = circX + 50;
					circY = circY + 50;
					textX = textX + 50;
					textY = textY + 50;
				}
				else
				{
					circX = circX + 50;
					circY = circY + 50;
					textX = textX + 50;
					textY = textY + 50;
					node->right = newNode;
					node->right->tree.Insert(data, circX, circY, textX, textY);
					newNode->x = circX;
					newNode->y = circY;
					newNode->tx = textX;
					newNode->ty = textY;
					break;
				}
			}
			else
			{
				if (node->tree.Insert(data, circX, circY, textX, textY) == false)
				{
					return false;
				}
				break;
			}
		}
	}
	conversion(root, circX, circY, textX, textY);
	return true;
}
Node* AVL::search(int data)
{
	int key = data % 10;
	AVLNode* node = root;
	Node* found;
	while (node)
	{
		if (node->data == key)
		{
			found = node->tree.Search(data);
			cout << "Node Found" << endl;
			return found;
		}
		else if (key < node->data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	cout << "Data not Found" << endl;
	return NULL;
}
void AVL::preorder(AVLNode* node)
{
	if (node != NULL)
	{
		cout << node->data << " ";
		node->tree.display(node->tree.Root);
		cout << endl;
		preorder(node->left);
		preorder(node->right);
	}
}
int AVL::Height(AVLNode* node)
{
	int left = 0;
	int right = 0;
	if (node == NULL)
	{
		return -1;
	}
	else
	{
		left = Height(node->left);
		right = Height(node->right);

		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}
void AVL::conversion(AVLNode*& p , int& circX, int& circY, int& textX, int& textY)
{
	if (p != NULL)
	{
		conversion(p->left, circX, circY, textX, textY);
		conversion(p->right, circX, circY, textX, textY);
		if (bf(p) > 1)
		{
			if (bf(p->left) > 0)
			{
				rrrotation(p, circX, circY, textX, textY);
			}
			else
			{
				llrotation(p->left, circX, circY, textX, textY);
				rrrotation(p, circX, circY, textX, textY);
			}
		}
		else if (bf(p) < -1)
		{
			if (bf(p->right) < 0)
			{
				llrotation(p, circX, circY, textX, textY);
			}
			else
			{
				rrrotation(p->right, circX, circY, textX, textY);
				llrotation(p, circX, circY, textX, textY);
			}
		}
	}
}
int AVL::bf(AVLNode* p)
{
	if (p == NULL)
	{
		return 0;
	}
	return Height(p->left) - Height(p->right);
}
void AVL::rrrotation(AVLNode*& p, int& circX, int& circY, int& textX, int& textY)
{
	AVLNode* tree = p->left;
	AVLNode* t2 = tree->right;
	tree->right = p;
	p->left = t2;
	p = tree;
}
void AVL::llrotation(AVLNode*& p, int& circX, int& circY, int& textX, int& textY)
{
	AVLNode* tree = p->right;
	AVLNode* t2 = tree->left;
	tree->left = p;
	p->right = t2;
	p = tree;
}

bool BST::Insert(int data, int& circX, int& circY, int& textX, int& textY)
{
	Node* newNode = new Node;
	newNode->data = data;
	Node* temp = Root;
	//circX = 550;
	//circY = 100;
	//textX = 560;
	//textY = 105;
	if (Root == NULL)
	{
		Root = newNode;
		return true;
	}
	else
	{
		while (true)
		{

			if (data < temp->data)
			{
				if (temp->left != NULL)
				{
					//circX = circX - 50;
					//circY = circY + 50;
					//textX = textX - 50;
					//textY = textY + 50;
					temp = temp->left;
				}
				else
				{
					//circX = circX - 50;
					//circY = circY + 50;
					//textX = textX - 50;
					//textY = textY + 50;
					temp->left = newNode;
					//temp->x = circX;
					//temp->y = circY;
					//temp->tx = textX;
					//temp->ty = textY;
					break;
				}
			}
			else if (data > temp->data)
			{
				if (temp->right != NULL)
				{
					temp = temp->right;
				}
				else
				{
					//circX = circX + 50;
					//circY = circY + 50;
					//textX = textX + 50;
					//textY = textY + 50;
					temp->right = newNode;
					//temp->x = circX;
					//temp->y = circY;
					//temp->tx = textX;
					//temp->ty = textY;
					break;
				}
			}
			else
			{
				cout << "Duplicate Data!" << endl;
				return false;
			}
		}
		cout << "Data entered!" << endl;
		return true;
	}
}
Node* BST::Search(int data)
{
	Node* temp = Root;
	while (temp != NULL)
	{
		if (temp->data == data)
		{
			return temp;
		}
		else if (data < temp->data)
		{
			temp = temp->left;
		}
		else if (data > temp->data)
		{
			temp = temp->right;
		}
		else
		{
			return NULL;
		}
	}
}
void BST::display(Node* root)
{
	Node* curr = root;
	if (curr != NULL)
	{
		cout << curr->data << " ";
		display(curr->left);
		display(curr->right);
	}
}
