#include "TreeNode.h"

TreeNode::TreeNode(int npid, int nid, std::string name,
	int alter, double einkommen, int plz)
{
	this->NodePosID = npid;
	this->NodeID = nid;
	this->Name = name;
	this->Alter = alter;
	this->Einkommen = einkommen;
	this->PLZ = plz;

	this->left = nullptr;
	this->right = nullptr;

	//this->parentNode = nullptr; // Würde bedeuten Knoten ist Wurzel, wenn es nicht auf etwas anderes zeigen würde
}

void TreeNode::print()
{
	std::cout
		<< "NodeID: " << this->NodeID << ", "
		<< "Name: " << this->Name << ", "
		<< "Alter: " << this->Alter << ", "
		<< "Einkommen: " << this->Einkommen << ", "
		<< "PLZ: " << this->PLZ << ", "
		<< "PosID: " << this->NodePosID
		<< std::endl;
}

bool TreeNode::getRed()
{
	return this->red;
}

void TreeNode::setRed(bool v)
{
	this->red = v;
}

int TreeNode::getNodePosID()
{
	return this->NodePosID;
}

void TreeNode::setNodePosID(int npid)
{
	this->NodePosID = npid;
}

int TreeNode::getNodeID()
{
	return this->NodeID;
}

void TreeNode::setNodeID(int nid)
{
	this->NodeID = nid;
}

std::string TreeNode::getName()
{
	return this->Name;
}

void TreeNode::setName(std::string name)
{
	this->Name = name;
}

int TreeNode::getAlter()
{
	return this->Alter;
}

void TreeNode::setAlter(int alter)
{
	this->Alter = alter;
}

double TreeNode::getEinkommen()
{
	return this->Einkommen;
}

void TreeNode::setEinkommen(double einkommen)
{
	this->Einkommen = einkommen;
}

int TreeNode::getPLZ()
{
	return this->PLZ;
}

void TreeNode::setPLZ(int plz)
{
	this->PLZ = plz;
}

TreeNode* TreeNode::getLeft()
{
	return this->left;
}

void TreeNode::setLeft(TreeNode* l)
{
	this->left = l;
}

TreeNode* TreeNode::getRight()
{
	return this->right;
}

void TreeNode::setRight(TreeNode* r)
{
	this->right = r;
}
/*
TreeNode* TreeNode::getParent()
{
	return this->parentNode;
}

void TreeNode::setParent(TreeNode* p)
{
	this->parentNode = p;
}*/
