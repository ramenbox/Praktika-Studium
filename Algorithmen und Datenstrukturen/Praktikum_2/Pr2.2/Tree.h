/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree{
	
	private: 
		TreeNode* anker;
		int NodeIDCounter;
	
	public:
		Tree();

		// Zum Einfügen eines neuen Knoten im Baum
		void addNode(std::string, int, double, int);
		// Zum Suchen mehrerer Knoten mit dem gleichen Namen durch die Tiefensuche
		bool searchNode(std::string);
		void deleteNode(int);
		void printAll();

		//Hilfs-Methoden
		TreeNode* blattknoten(TreeNode*, int);
		void tiefensuche(TreeNode*, std::string, bool&);
		TreeNode* findNode(TreeNode*, int);
		TreeNode* findParentNode(TreeNode*, TreeNode*);
		TreeNode* minNodeL(TreeNode*);
		TreeNode* minNodeR(TreeNode*);
		void preOrderPrint(TreeNode*);

		// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
		friend TreeNode * get_anker(Tree& TN);
};
