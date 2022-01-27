/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;


Tree::Tree()
{
	this->anker = nullptr;
	this->NodeIDCounter = 0;
}

void Tree::addNode(std::string Name, int Alter, double Einkommen, int PLZ)
{
	TreeNode* neuerKnoten = new TreeNode(
		Alter + PLZ + Einkommen,	 // Formel für den Positionsindikator
		this->NodeIDCounter++,		 // Chronologischer Ablauf
		Name, Alter, Einkommen, PLZ	 // Datensatz
	);

	if (this->anker)
	{
		// Finde den Blattknoten passend zum Positionsindikator des neuen Knotens
		TreeNode* blattKnoten = blattknoten(this->anker, neuerKnoten->getNodePosID());
		
		// Bestimme wo der neue Knoten am Blattknoten eingebaut werden soll
		if (neuerKnoten->getNodePosID() >= blattKnoten->getNodePosID())
		{
			blattKnoten->setRight(neuerKnoten);
		}
		else
		{
			blattKnoten->setLeft(neuerKnoten);
		}
	}
	else // leerer Baum
	{
		this->anker = neuerKnoten;
	}

}

bool Tree::searchNode(std::string name)
{
	bool flag = false; // unser Rückgabewert am Ende
	// Baum darf nicht leer sein
	if (this->anker)
		this->tiefensuche(this->anker, name, flag);
	return flag;
}

void Tree::deleteNode(int npid)
{
	if (this->anker)
	{
		TreeNode* tmpNode = this->findNode(this->anker, npid);
		// Suche den Vorgänger von tmpNode
		if (!tmpNode)
		{
			std::cout << "\r+ PosID ist ungueltig! Es wurde nichts geloescht.";
			return;
		}
		TreeNode* parentNode = this->findParentNode(this->anker, tmpNode);
		
		// 1. Fall: ... ist Wurzel
		if (!parentNode)
		{
			// Minimum des rechten Teilbaums
			TreeNode* minRightNode = nullptr;
			if (tmpNode->getRight())
				minRightNode = minNodeL(tmpNode->getRight());
			else if (tmpNode->getLeft())
				minRightNode = minNodeR(tmpNode->getLeft());

			if (minRightNode)
			{
				// Vorgänger vom kleinstem Knoten des rechten Teilbaums
				TreeNode* preMinRNode = this->findParentNode(this->anker, minRightNode);


				// Bestimme den Nachfolger von minRightNode
				TreeNode* minRNChild = nullptr;
				if (minRightNode->getLeft())
				{
					minRNChild = minRightNode->getLeft();
				}
				else
				{
					minRNChild = minRightNode->getRight();
				}

				// Nachfolger ist linker Knoten vom Vorgänger
				if (preMinRNode->getLeft() == minRightNode)
				{
					preMinRNode->setLeft(minRNChild);
				}
				// Nachfolger ist rechter Knoten vom Vorgänger
				else if (preMinRNode->getRight() == minRightNode)
				{
					preMinRNode->setRight(minRNChild);
				}

				// Ersetze Wurzel
				minRightNode->setLeft(tmpNode->getLeft());
				minRightNode->setRight(tmpNode->getRight());

				this->anker = minRightNode;

				delete tmpNode;
			}
			else
			{
				delete tmpNode;
				this->anker = nullptr;
			}
			

		}
		// 2. Fall: ... hat keine Nachfolger
		else if (!tmpNode->getLeft() && !tmpNode->getRight())
		{
			// Bestimme ob Nachfolger linker oder rechter Knoten ist vom Vorgänger
			if (parentNode->getLeft() == tmpNode && parentNode->getRight() != tmpNode)
			{
				// Setze diesen gemäß dessen auf nullptr
				parentNode->setLeft(nullptr);
			}
			else
			{
				parentNode->setRight(nullptr);
			}
			delete tmpNode;
		}
		// 3. Fall: ... hat nur einen Nachfolger (rechts oder links)
		else if (tmpNode->getLeft() && !tmpNode->getRight()) // Linker Nachfolger
		{
			// Bestimme ob Nachfolger linker oder rechter Knoten ist vom Vorgänger
			if (parentNode->getLeft() == tmpNode)
			{
				// Setze diesen auf linker Nachfolger von tmpNode
				parentNode->setLeft(tmpNode->getLeft());
			}
			else
			{
				// Setze diesen auf rechter Nachfolger von tmpNode
				parentNode->setRight(tmpNode->getLeft());
			}
			delete tmpNode;
		}
		else if (!tmpNode->getLeft() && tmpNode->getRight()) // Rechter Nachfolger
		{
			// Bestimme ob Nachfolger linker oder rechter Knoten ist vom Vorgänger
			if (parentNode->getLeft() == tmpNode)
			{
				// Setze diesen auf linker Nachfolger von tmpNode
				parentNode->setLeft(tmpNode->getRight());
			}
			else
			{
				// Setze diesen auf rechter Nachfolger von tmpNode
				parentNode->setRight(tmpNode->getRight());
			}
			delete tmpNode;
		}
		// 4. Fall: ... hat zwei Nachfolger
		//TODO
		else
		{
			// Minimum des rechten Teilbaums
			TreeNode* minRightNode = nullptr;
			if (tmpNode->getRight())
				minRightNode = minNodeL(tmpNode->getRight());
			else if (tmpNode->getLeft())
				minRightNode = minNodeR(tmpNode->getLeft());

			if (minRightNode)
			{
				// Vorgänger vom kleinstem Knoten des rechten Teilbaums
				TreeNode* preMinRNode = this->findParentNode(this->anker, minRightNode);


				// Bestimme den Nachfolger von minRightNode
				TreeNode* minRNChild = nullptr;
				if (minRightNode->getLeft())
				{
					minRNChild = minRightNode->getLeft();
				}
				else
				{
					minRNChild = minRightNode->getRight();
				}

				// Nachfolger ist linker Knoten vom Vorgänger
				if (preMinRNode->getLeft() == minRightNode)
				{
					preMinRNode->setLeft(minRNChild);
				}
				// Nachfolger ist rechter Knoten vom Vorgänger
				else if (preMinRNode->getRight() == minRightNode)
				{
					preMinRNode->setRight(minRNChild);
				}

				// Ersetze den Knoten
				minRightNode->setLeft(tmpNode->getLeft());
				minRightNode->setRight(tmpNode->getRight());

				if (parentNode->getLeft() == tmpNode)
					parentNode->setLeft(minRightNode);
				else
					parentNode->setRight(minRightNode);

				delete tmpNode;
			}
			else
			{
				delete tmpNode;
				this->anker = nullptr;
			}
		}
		this->NodeIDCounter--;
	}
}

void Tree::printAll()
{
	// PreOrder Ausgabe
	if (this->anker)
	{
		std::cout
			<< right
			<< "ID" << setw(3)
			<< "|" << setw(7)
			<< "Name" << setw(7)
			<< "|" << setw(7)
			<< "Alter" << setw(4)
			<< "|" << setw(11)
			<< "Einkommen" << setw(5)
			<< "|" << setw(5)
			<< "PLZ" << setw(5)
			<< "|" << setw(7)
			<< "PosID" << setw(5)
			<< std::endl;
		std::cout << "----+-------------+----------+---------------+---------+-----------" << endl;
		this->preOrderPrint(this->anker);
	}
	else
	{
		std::cout << "Leerer Baum: Baum hat keine Datensaetze." << std::endl;
	}
}


void Tree::preOrderPrint(TreeNode* node)
{
	// Root, Left, Right
	if (node)
	{
		std::cout
			<< right
			<< setw(4) << node->getNodeID() << "|"
			<< setw(13) << node->getName() << "|"
			<< setw(10) << node->getAlter() << "|"
			<< setw(15) << node->getEinkommen() << "|"
			<< setw(9) << node->getPLZ() << "|"
			<< setw(10) << node->getNodePosID()
			<< std::endl;
	}
	if (node->getLeft())
		preOrderPrint(node->getLeft());
	if (node->getRight())
		preOrderPrint(node->getRight());

}


TreeNode* Tree::blattknoten(TreeNode* current, int PositionsID)
{
	if (PositionsID >= current->getNodePosID()) // Rechter Teilbaum
	{
		if (current->getRight())
			return blattknoten(current->getRight(), PositionsID);
	}
	else										// Linker Teilbaum
	{
		if (current->getLeft())
			return blattknoten(current->getLeft(), PositionsID);
	}
	return current;
}

void Tree::tiefensuche(TreeNode* current, std::string name, bool& flag)
{
	// InOrder-Traversierung
	
	if (current->getLeft())
	{
		tiefensuche(current->getLeft(), name, flag);
	}

	// Ausgabe aller gefundenen Datensätze
	if (current->getName() == name)
	{
		if (!flag)
		{	// mindestens 1 Fundstelle
			std::cout << "+ Fundstellen: " << endl;
			flag = true;
		}
		current->print();
	}

	if (current->getRight())
	{
		tiefensuche(current->getRight(), name, flag);
	}
}

TreeNode* Tree::findNode(TreeNode* node, int npid)
{
	if (!node) // Basisfall
		return nullptr;
	else if (node->getNodePosID() == npid)
		return node;
	else
	{
		TreeNode* tmpNode = findNode(node->getLeft(), npid);
		if (tmpNode) return tmpNode; // Gesuchter Knoten im Linkem Teilbaum
		return findNode(node->getRight(), npid);
	}

}

TreeNode* Tree::findParentNode(TreeNode* current, TreeNode* childNode)
{
	// Basisfall
	if (!current) return nullptr;
	else
	{
		if (current->getLeft() == childNode || current->getRight() == childNode)
		{
			return current;
		}
		else
		{
			if (current->getNodePosID() < childNode->getNodePosID())
				return findParentNode(current->getRight(), childNode);
			else
				return findParentNode(current->getLeft(), childNode);
		}
	}

}

TreeNode* Tree::minNodeL(TreeNode* node)
{
	if (node->getLeft())
		return minNodeL(node->getLeft());
	return node;
}

TreeNode* Tree::minNodeR(TreeNode* node)
{
	if (node->getRight())
		return minNodeR(node->getRight());
	return node;
}

