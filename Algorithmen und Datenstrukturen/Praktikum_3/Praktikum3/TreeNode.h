#pragma once
#include <iostream>
#include <string>

class TreeNode
{
public:
	TreeNode(int, int, std::string, int, double, int);

	void print();

	// Ist Rot (true) oder Schwarz (false)
	bool getRed();
	// Setze true oder false
	void setRed(bool);

	int getNodePosID();
	void setNodePosID(int);

	int getNodeID();
	void setNodeID(int);

	std::string getName();
	void setName(std::string);

	int getAlter();
	void setAlter(int);

	double getEinkommen();
	void setEinkommen(double);

	int getPLZ();
	void setPLZ(int);

	TreeNode* getLeft();
	void setLeft(TreeNode*);

	TreeNode* getRight();
	void setRight(TreeNode*);

	//TreeNode* getParent();
	//void setParent(TreeNode*);

private:
	int NodePosID;
	int NodeID;
	bool red;
	std::string Name;
	int Alter;
	double Einkommen;
	int PLZ;

	TreeNode* left;
	TreeNode* right;

	// Hilfsattribute
	//TreeNode* parentNode; // Macht die Sache deutlich einfacher
};