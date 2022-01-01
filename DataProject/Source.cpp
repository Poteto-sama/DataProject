#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <queue>
using namespace sf;
using namespace std;
	Font font;
	RenderWindow window(VideoMode(1200, 600), "Avl/BST visualization", Style::Default);
	RenderTexture target;
	Event event;
	Text prompt;
	CircleShape cover;
	string fill;
	int jg = 0;
class Node
{
public:
	int data;
	Node* right, * left;
	Node();
};
class BST
{
public:
	Node* Root;
	BST();
	bool InsertBST(int data);
	bool SearchBST(int data);
	void postorderBST(Node* root, int x, int y);
	void toDisplayBST(Node* root, int x, int y);
	void searchHighlight(Node* root, int x, int y, int data);
	void toDisplaySearchBST(Node* node, int x, int y,int data);
};
class AVLNode
{
public:
	int data;
	AVLNode* right, * left;
	BST tree;
	AVLNode();
};
class AVL
{
public:
	AVLNode* root;
	int key;
	AVL();
	~AVL();
	bool insertAVL(int data);
	bool searchAVL(int key);
	void toDisplayAVL(AVLNode* p, int x, int y);
	void postorderAVL(AVLNode* node, int x, int y);
	void searchHighlight(AVLNode* root, int x, int y, int data);
	void toDisplaySearchAVL(AVLNode* node, int x, int y, int data);
	int heightAVL(AVLNode* node);
	void conversion(AVLNode*& p);
	int bf(AVLNode* p);
	void rrrotation(AVLNode*& p);
	void llrotation(AVLNode*& p);
};
Node::Node()
{
	right = left = NULL;
	data = 0;
}
AVLNode::AVLNode()
{
	right = left = NULL;
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
bool AVL::searchAVL(int data)
{
	int key = data % 10;
	AVLNode* node = root;
	bool found;
	while (node)
	{
		if (node->data == key)
		{
			searchHighlight(root, 550, 100, data);
			Sleep(4000);
			target.clear();
			window.clear();
			found = node->tree.SearchBST(data);
			if (found == true)
			{
				return true;
			}
			else if (found == false)
			{
					prompt.setCharacterSize(30);
					prompt.setFillColor(Color(204, 16, 60));
					prompt.setFont(font);
					prompt.setPosition(450, 500);
					prompt.setString("Data not Found!");
					target.draw(prompt);
					window.draw(Sprite(target.getTexture()));
					window.display();
					Sleep(3000);
				return false;
			}
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
	searchHighlight(root, 550, 100, data);
	Sleep(3000);
	prompt.setCharacterSize(30);
	prompt.setFillColor(Color(204, 16, 60));
	prompt.setFont(font);
	prompt.setPosition(450, 500);
	prompt.setString("Key does not Exist!");
	target.draw(prompt);
	window.draw(Sprite(target.getTexture()));
	window.display();
	Sleep(3000);
	target.clear();
	window.clear();
	return false;
}
bool AVL::insertAVL(int data)
{
	int key = data % 10;
	AVLNode* newNode = new AVLNode;
	newNode->data = key;
	newNode->left = NULL;
	newNode->right = NULL;
	AVLNode* node = root;
	if (root == NULL)
	{
		root = newNode;
		node = newNode;
		newNode->tree.InsertBST(data);
	}
	else
	{
		while (1)
		{
			if (key < node->data)
			{
				if (node->left != NULL)
				{
					node = node->left;
				}
				else
				{
					node->left = newNode;
					node->left->tree.InsertBST(data);
					break;
				}
			}
			else if (key > node->data)
			{
				if (node->right != NULL)
				{
					node = node->right;
				}
				else
				{
					node->right = newNode;
					node->right->tree.InsertBST(data);
					break;
				}
			}
			else if(key == node->data)
			{
				if (node->tree.InsertBST(data) == false)
				{
					return false;
				}
				break;
			}
		}
	}
	conversion(root);
	return true;
}
int AVL::bf(AVLNode* p)
{
	if (p == NULL)
	{
		return 0;
	}
	return (heightAVL(p->left) - heightAVL(p->right));
}
void AVL::llrotation(AVLNode*& p)
{
	AVLNode* T1 = p->right;
	p->right->right;
	AVLNode* T2 = T1->left;
	if (T1->left == NULL)
	{}
	T1->left = p;
	p->right = T2;
	p = T1;
}
void AVL::rrrotation(AVLNode*& p)
{
	AVLNode* T1 = p->left;
	AVLNode* T2 = T1->right;
	if (T1->right == NULL)
	{}
	T1->right = p;
	p->left = T2;
	p = T1;
}
void AVL::conversion(AVLNode*& p)
{
	int balFac;
	if (p != NULL)
	{
		if (jg == 0)
		{
			jg++;
			conversion(p->left);
			conversion(p->right);
		}
		conversion(p->left);
		conversion(p->right);
		balFac = bf(p);
		if (balFac > 1)
		{
			if (bf(p->left) > 0)
			{
				rrrotation(p);
			}
			else
			{
				llrotation(p->left);
				rrrotation(p);
			}
		}
		else if (balFac < -1)
		{
			if (bf(p->right) < 0)
			{
				llrotation(p);
			}
			else
			{
				rrrotation(p->right);
				llrotation(p);
			}
		}
	}
}
bool BST::InsertBST(int data)
{
	Node* newNode = new Node;
	newNode->data = data;
	Node* node = Root;
	if (Root == NULL)
	{
		Root = newNode;
		node = newNode;
		postorderBST(newNode, 550, 100);
		return true;
	}
	else
	{
		while (true)
		{
			if (data < node->data)
			{
				if (node->left != NULL)
				{
					node = node->left;
				}
				else
				{
					node->left = newNode;
					break;
				}
			}
			else if (data > node->data)
			{
				if (node->right != NULL)
				{
					node = node->right;
				}
				else
				{
					node->right = newNode;
					break;
				}
			}
			else
			{
				postorderBST(Root, 550, 100);
				prompt.setCharacterSize(30);
				prompt.setFillColor(Color(204, 16, 60));
				prompt.setFont(font);
				prompt.setPosition(450, 500);
				prompt.setString("Duplicate Data!");
				target.draw(prompt);
				window.draw(Sprite(target.getTexture()));
				window.display();
				Sleep(3000);
				return false;
			}
		}
		cout << "Data entered!" << endl;
		postorderBST(Root, 550, 100);
		return true;
	}
}
bool BST::SearchBST(int data)
{
	Node* node = Root;
	while (node != NULL)
	{
		if (node->data == data)
		{
			searchHighlight(Root, 550, 100, data);
			return true;
		}
		else if (data < node->data)
		{
			node = node->left;
		}
		else if (data > node->data)
		{
			node = node->right;
		}
		else
		{
			searchHighlight(Root, 550, 100, data);
			return false;
		}
	}
	searchHighlight(Root, 550, 100, data);
	return false;
}
int AVL::heightAVL(AVLNode* p)
{
	int left, right;
	if (p == NULL)
	{
		return -1;
	}
	else 
	{
		left = heightAVL(p->left);
		right = heightAVL(p->right);
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
void AVL::postorderAVL(AVLNode* node, int x, int y)
{
	AVLNode* curr = node;
	int height = heightAVL(curr);
	if (node != NULL)
	{
		if (height == 1)
		{
			postorderAVL(curr->left, x - 30, y + 50);
			postorderAVL(curr->right, x + 30, y + 50);
		}
		if (height == 2)
		{
			postorderAVL(curr->left, x - 70, y + 50);
			postorderAVL(curr->right, x + 70, y + 50);
		}
		if (height == 3)
		{
			postorderAVL(curr->left, x - 110, y + 50);
			postorderAVL(curr->right, x + 110, y + 50);
		}
		toDisplayAVL(curr, x, y);
	}
}
int findDepth(Node* root, int x)
{
	if (root == NULL)
	{
		return -1;
	}
	int dist = -1;
	if ((root->data == x) || (dist = findDepth(root->left, x)) >= 0 || (dist = findDepth(root->right, x)) >= 0)
	{
		return dist + 1;
	}
	return dist;
}
int find(Node* root, int t, int l)
{
	if (!root)
	{
		return 0;
	}
	if (root->data == t)
	{
		return l;
	}
	int x = find(root->left, t, l + 1);
	if (x != 0)
	{
		return x;
	}
	x = find(root->right, t, l + 1);
	return x;
}
int getLevel(struct Node* node, int target)
{
	if (!node)
	{
		return 0;
	}
	int l = 1;
	return find(node, target, l);
}
void BST::postorderBST(Node* root, int x, int y)
{
	Node* curr = root;
	if (curr != NULL)
	{
		int height = getLevel(Root, root->data);
		if (height == 5)
		{
			postorderBST(curr->left, x - 30, y + 50);
			postorderBST(curr->right, x + 30, y + 50);
		}
		if (height == 4)
		{
			postorderBST(curr->left, x - 65, y + 50);
			postorderBST(curr->right, x + 65, y + 50);
		}
		if (height == 3)
		{
			postorderBST(curr->left, x - 75, y + 50);
			postorderBST(curr->right, x + 75, y + 50);
		}
		if (height == 2)
		{
			postorderBST(curr->left, x - 110, y + 50);
			postorderBST(curr->right, x + 110, y + 50);
		}
		if (height == 1)
		{
			postorderBST(curr->left, x - 135, y + 50);
			postorderBST(curr->right, x + 135, y + 50);
		}
		toDisplayBST(curr, x, y);
	}
}
void AVL::searchHighlight(AVLNode* node, int x, int y, int data)
{
	AVLNode* curr = node;
	int height = heightAVL(curr);
	if (node != NULL)
	{
		if (height == 1)
		{
			searchHighlight(curr->left, x - 30, y + 50,data);
			searchHighlight(curr->right, x + 30, y + 50,data);
		}
		if (height == 2)
		{
			searchHighlight(curr->left, x - 70, y + 50,data);
			searchHighlight(curr->right, x + 70, y + 50,data);
		}
		if (height == 3)
		{
			searchHighlight(curr->left, x - 110, y + 50,data);
			searchHighlight(curr->right, x + 110, y + 50,data);
		}
		cout << node->data << " ";
		toDisplaySearchAVL(curr, x, y,data);
	}
}
void BST::searchHighlight(Node* root, int x, int y, int data)
{
	Node* curr = root;
	if (curr != NULL)
	{
		int height = getLevel(Root, root->data);
		if (height == 5)
		{
			searchHighlight(curr->left, x - 30, y + 50, data);
			searchHighlight(curr->right, x + 30, y + 50,data);
		}
		if (height == 4)
		{
			searchHighlight(curr->left, x - 50, y + 50,data);
			searchHighlight(curr->right, x + 50, y + 50,data);
		}
		if (height == 3)
		{
			searchHighlight(curr->left, x - 70, y + 50,data);
			searchHighlight(curr->right, x + 70, y + 50,data);
		}
		if (height == 2)
		{
			searchHighlight(curr->left, x - 100, y + 50,data);
			searchHighlight(curr->right, x + 100, y + 50,data);
		}
		if (height == 1)
		{
			searchHighlight(curr->left, x - 150, y + 50,data);
			searchHighlight(curr->right, x + 150, y + 50,data);
		}
		cout << curr->data << " ";
		toDisplaySearchBST(curr, x, y,data);
	}
}
void AVL::toDisplaySearchAVL(AVLNode* node, int x, int y, int data)
{
	if (node->data == data % 10)
	{
		cover.setOutlineColor(Color(84, 185, 77));
	}
	else
	{
		cover.setOutlineColor(Color(30, 175, 175));
	}
	string fill;
	cover.setRadius(18);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(4);
	fill = to_string(node->data);
	prompt.setCharacterSize(50);
	prompt.setFillColor(Color::White);
	prompt.setFont(font);
	prompt.setPosition(340, 0);
	prompt.setString("A V L HashTable");
	target.draw(prompt);
	prompt.setCharacterSize(18);
	prompt.setFillColor(Color::Black);
	prompt.setFont(font);
	prompt.setPosition(x + 10, y + 5);
	prompt.setString(fill);
	cover.setPosition(x, y);
	target.draw(cover, BlendNone);
	target.draw(prompt);
	target.display();
	window.draw(Sprite(target.getTexture()));
	window.display();
}
void AVL::toDisplayAVL(AVLNode* node, int x, int y)
{
	string fill;
	cover.setRadius(18);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(4);
	cover.setOutlineColor(Color(30, 175, 175));
	fill = to_string(node->data);
	prompt.setCharacterSize(50);
	prompt.setFillColor(Color::White);
	prompt.setFont(font);
	prompt.setPosition(340, 0);
	prompt.setString("A V L HashTable");
	target.draw(prompt);
	prompt.setCharacterSize(18);
	prompt.setFillColor(Color::Black);
	prompt.setFont(font);
	prompt.setPosition(x + 10, y + 5);
	prompt.setString(fill);
	cover.setPosition(x, y);
	target.draw(cover, BlendNone);
	target.draw(prompt);
	target.display();
	window.draw(Sprite(target.getTexture()));
	window.display();
}
void BST::toDisplayBST(Node* node, int x, int y)
{
	string fill;
	cover.setRadius(18);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(4);
	cover.setOutlineColor(Color(30, 175, 175));
	fill = to_string(node->data);
	prompt.setCharacterSize(50);
	prompt.setFillColor(Color::White);
	prompt.setFont(font);
	prompt.setPosition(340, 0);
	prompt.setString("B S T Container");
	target.draw(prompt);
	prompt.setCharacterSize(20);
	prompt.setFillColor(Color::Black);
	prompt.setFont(font);
	prompt.setPosition(x + 6, y + 3);
	prompt.setString(fill);
	cover.setPosition(x, y);
	target.draw(cover, BlendNone);
	target.draw(prompt);
	target.display();
	window.draw(Sprite(target.getTexture()));
	window.display();
}
void BST::toDisplaySearchBST(Node* node, int x, int y, int data)
{
	if (node->data == data)
	{
		cover.setOutlineColor(Color(84, 185, 77));
	}
	else
	{
		cover.setOutlineColor(Color(30, 175, 175));
	}
	string fill;
	cover.setRadius(18);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(4);
	fill = to_string(node->data);
	prompt.setCharacterSize(50);
	prompt.setFillColor(Color::White);
	prompt.setFont(font);
	prompt.setPosition(340, 0);
	prompt.setString("B S T Container");
	target.draw(prompt);
	prompt.setCharacterSize(20);
	prompt.setFillColor(Color::Black);
	prompt.setFont(font);
	prompt.setPosition(x + 6, y + 3);
	prompt.setString(fill);
	cover.setPosition(x, y);
	target.draw(cover, BlendNone);
	target.draw(prompt);
	target.display();
	window.draw(Sprite(target.getTexture()));
	window.display();
}
int main()
{
	string choice;
	AVL hash;
	bool var = 0;
	if (!font.loadFromFile("Maves-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}
	window.setVerticalSyncEnabled(true);
	if (!target.create(window.getSize().x, window.getSize().y))
	{
		return -1;
	}
	target.clear(Color::Black);
	window.clear();
	target.display();
	CircleShape cover;
	cover.setRadius(20);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(3);
	cover.setOutlineColor(Color(60, 30, 165));
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			target.clear();
			window.clear();
			while (choice != "0")
			{
				cout << "1:Insert Data" << endl << "2:Search" << endl << "0:Terminate" << endl;
				cout << "Enter: ";
				cin >> choice;
				if (choice == "1")
				{
					window.clear();
					target.clear();
					int data;
					int key;
					cout << "Please enter data: ";
					cin >> data;
					var = hash.insertAVL(data);
					prompt.setCharacterSize(50);
					prompt.setFillColor(Color::White);
					prompt.setFont(font);
					prompt.setPosition(340, 0);
					prompt.setString("B S T Container");
					target.draw(prompt);
					window.draw(Sprite(target.getTexture()));
					window.display();
					Sleep(3000);
					window.clear();
					target.clear();
					int x = 550, y = 100;
					prompt.setCharacterSize(50);
					prompt.setFillColor(Color::White);
					prompt.setFont(font);
					prompt.setPosition(340, 0);
					prompt.setString("A V L HashTable");
					target.draw(prompt);
					hash.postorderAVL(hash.root, x, y);
				}
				else if (choice == "2")
				{
					int x = 550, y = 100;
					int data;
					cout << "Please enter data to search: ";
					cin >> data;
					window.clear();
					target.clear();
					hash.searchAVL(data);
					Sleep(3000);
					target.clear();
					window.clear();
					hash.postorderAVL(hash.root, x, y);
				}
				else if (choice == "0")
				{
					target.clear();
					window.clear();
					window.display();
					prompt.setCharacterSize(70);
					prompt.setFillColor(Color(190, 90, 65));
					prompt.setFont(font);
					prompt.setPosition(270, 270);
					prompt.setString("Balance me, senpai");
					target.draw(prompt);
					window.draw(Sprite(target.getTexture()));
					window.display();
					prompt.setCharacterSize(70);
					prompt.setFillColor(Color::White);
					prompt.setFont(font);
					prompt.setPosition(300, 350);
					prompt.setString("Thank you :)");
					target.draw(prompt);
					window.draw(Sprite(target.getTexture()));
					window.display();
					Sleep(3000);
					return 0;
				}
				else
				{
					cout << "Invalid Input! Please try again." << endl;
				}
				window.draw(Sprite(target.getTexture()));
				window.display();
			}
		}
	}
	Text prompt1("Haha BSDK", font, 50);
	return 0;
}