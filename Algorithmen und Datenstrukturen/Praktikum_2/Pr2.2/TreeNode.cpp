/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>


TreeNode::TreeNode(int nipd, int nid, string name, int alter, double einkommen, int plz)
{
	this->NodePosID = nipd;
	this->NodeID = nid;
	this->Name = name;
	this->Einkommen = einkommen;
	this->Alter = alter;
	this->PLZ = plz;

	this->left = nullptr;
	this->right = nullptr;
}

int TreeNode::getNodePosID()
{
	return this->NodePosID;
}

int TreeNode::getNodeID()
{
	return this->NodeID;
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

TreeNode* TreeNode::getRight()
{
	return this->right;
}

void TreeNode::setLeft(TreeNode* l)
{
	this->left = l;
}

void TreeNode::setRight(TreeNode* r)
{
	this->right = r;
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
