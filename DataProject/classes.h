#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Node
{
public:
	int data;
	int x, y;
	int tx, ty;
	Node* right, * left;
	Node();
};

class BST
{
public:
	Node* Root;
	BST();
	bool Insert(int data, int& circX, int& circY, int& textX, int& textY);
	Node* Search(int data);
	void display(Node* root);
};

class AVLNode
{
public:
	int data;
	int x, y;
	int tx, ty;
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
	bool insert(int data,int &circX,int &circY,int &textX,int &textY, int &key);
	Node* search(int key);
	void preorder(AVLNode* node);
	int Height(AVLNode* node);
	void conversion(AVLNode*& p, int& circX, int& circY, int& textX, int& textY);
	int bf(AVLNode* p);
	void rrrotation(AVLNode*& p, int& circX, int& circY, int& textX, int& textY);
	void llrotation(AVLNode*& p, int& circX, int& circY, int& textX, int& textY);
};