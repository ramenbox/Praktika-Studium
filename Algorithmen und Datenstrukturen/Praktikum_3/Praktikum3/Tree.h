#pragma once
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue> 

class Tree
{
public:
	Tree();
	~Tree();

	bool addNode(std::string, int, double, int);
	bool searchNode(std::string);
	void printAll(void);
	void printInOrder(void);
	void printLevelOrder(void);
	void printLevelOrder234Tree(void);
	void deleteNode(int npid);

	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
	friend TreeNode* get_anker(Tree& TN);

private:
	TreeNode* anker;
	int NodeIDCounter;


	bool split4Node(TreeNode*);
	bool rotateTreeRight(TreeNode*, TreeNode*);
	bool rotateTreeLeft(TreeNode*, TreeNode*);

	// Hilfsfunktionen
	void searchPreOrder(TreeNode*, std::string, bool&);
	void balanceRBTree(std::vector<TreeNode*>); // Perfectly balanced, as all things should be

	TreeNode* findNode(TreeNode*, int);
	TreeNode* minNodeL(TreeNode*);
	TreeNode* minNodeR(TreeNode*);

	void inOrderPrint(TreeNode*);
	void preOrderPrint(TreeNode*);
	void postOrderDel(TreeNode*);

	int height(TreeNode*);

	// Finde Elternknoten - ohne Parent Pointer in TreeNode*
	TreeNode* findParentNode(TreeNode*, TreeNode*);
};
