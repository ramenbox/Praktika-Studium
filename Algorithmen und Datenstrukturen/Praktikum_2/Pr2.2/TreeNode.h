/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode{
	
	private:
		int NodePosID,
			NodeID,
			Alter,
			PLZ;
		double Einkommen;
		std::string Name;

		TreeNode* left, 
				* right;

	
	public:
		TreeNode(int, int, string, int, double, int);

		int getNodePosID();
		int getNodeID();

		std::string getName();
		void setName(std::string);

		int getAlter();
		void setAlter(int);

		double getEinkommen();
		void setEinkommen(double);

		int getPLZ();
		void setPLZ(int);

		// Linker/Rechter Kindesknoten
		TreeNode* getLeft();
		TreeNode* getRight();

		void setLeft(TreeNode*);
		void setRight(TreeNode*);

		void print();
};
