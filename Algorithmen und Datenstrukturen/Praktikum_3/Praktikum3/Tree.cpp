#include "Tree.h"

Tree::Tree()
{
	this->anker = nullptr;
	this->NodeIDCounter = 0;
}

Tree::~Tree()
{
}

void Tree::postOrderDel(TreeNode* node)
{
	if (node->getLeft())
		postOrderDel(node->getLeft());
	if (node->getRight())
		postOrderDel(node->getRight());
	if (node)
	{
		delete node;
		node = nullptr;
		this->NodeIDCounter--;
	}
}

bool Tree::addNode(std::string name, int alter, double einkommen, int plz)
{
	TreeNode* neuerKnoten = new TreeNode(
		alter+plz+einkommen,			// Positionsindikator
		++this->NodeIDCounter,			// Chronologisch
		name, alter, einkommen, plz);   // Datensätze
	neuerKnoten->setRed(true);			// Neue Knoten sind Rot

	TreeNode* tmp = this->anker;
	TreeNode* elternKnoten = nullptr;
	std::vector<TreeNode*> pfadKnoten;	// Für mögliche Rotationen
	while (tmp != nullptr)
	{
		elternKnoten = tmp;	// Merke Elternknoten
		pfadKnoten.push_back(tmp); // Merke Knoten im Suchpfad

		//nur schwarzer knoten
		if (!tmp->getRed())
		{
			if (this->split4Node(tmp))
			{
				//bool?
			}
		}

		// Traversierung der Suchrichtung
		if (neuerKnoten->getNodePosID() < tmp->getNodePosID())
		{
			tmp = tmp->getLeft();
		}
		else
		{
			tmp = tmp->getRight();
		}
	}

	// Hinzugefügter Knoten gehört auch in den Pfad
	pfadKnoten.push_back(neuerKnoten);

	// Fall 1: Leerer Baum
	if (elternKnoten == nullptr)
	{
		this->anker = neuerKnoten;
		neuerKnoten->setRed(false); // Wurzelknoten ist schwarz

		return true;
	}
	// Fall 2: Neuer Knoten links am Baum einfügen
	else if (neuerKnoten->getNodePosID() < elternKnoten->getNodePosID())
	{
		elternKnoten->setLeft(neuerKnoten);
		//neuerKnoten->setParent(elternKnoten);

		// Korrigiere Rot-Schwarz Baum nach der Regel
		// Bottom-Up
		this->balanceRBTree(pfadKnoten);

		return true;
	}
	// Fall 3: Neuer Knoten rechts am Baum einfügen
	else
	{
		elternKnoten->setRight(neuerKnoten);
		//neuerKnoten->setParent(elternKnoten);

		// Korrigiere Rot-Schwarz Baum nach der Regel
		// Bottom-Up
		this->balanceRBTree(pfadKnoten);

		return true;
	}


	return false;
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

// Suche Knoten mit dem gegebenen Namen
bool Tree::searchNode(std::string name)
{
	bool found = false;
	if (this->anker) searchPreOrder(this->anker, name, found);
	
	return found;
}

void Tree::printAll(void)
{
	// PreOrder Ausgabe
	if (this->anker && this->NodeIDCounter > 0)
	{
		std::cout
			<< std::right
			<< "ID" << std::setw(3)
			<< "|" << std::setw(7)
			<< "Name" << std::setw(7)
			<< "|" << std::setw(7)
			<< "Alter" << std::setw(4)
			<< "|" << std::setw(11)
			<< "Einkommen" << std::setw(5)
			<< "|" << std::setw(5)
			<< "PLZ" << std::setw(5)
			<< "|" << std::setw(7)
			<< "PosID" << std::setw(4)
			<< "|" << std::setw(4)
			<< "RED" << std::setw(4)
			<< std::endl;
		std::cout << "----+-------------+----------+---------------+---------+----------+------------" << std::endl;
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
			<< std::right
			<< std::setw(4) << node->getNodeID() - 1 << "|"
			<< std::setw(13) << node->getName() << "|"
			<< std::setw(10) << node->getAlter() << "|"
			<< std::setw(15) << node->getEinkommen() << "|"
			<< std::setw(9) << node->getPLZ() << "|"
			<< std::setw(10) << node->getNodePosID() << "|"
			<< std::setw(4) << node->getRed()
			<< std::endl;
	}
	if (node->getLeft())
		preOrderPrint(node->getLeft());
	if (node->getRight())
		preOrderPrint(node->getRight());

}

void Tree::printInOrder(void)
{
	if (this->anker)
	{
		std::cout << "InOrder: ";
		this->inOrderPrint(this->anker);
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Leerer Baum." << std::endl;
	}
}

void Tree::inOrderPrint(TreeNode* node)
{
	// Links, Wurzel, Rechts
	if (node)
	{
		this->inOrderPrint(node->getLeft());
		std::cout << node->getNodePosID() << " ";
		this->inOrderPrint(node->getRight());
	}
}

void Tree::printLevelOrder(void)
{
	if (this->anker)
	{
		// Schöne Formatierung
		std::cout << "Ausgabe in LeveLorder als binaerer Suchbaum:" << std::endl << std::endl;
		std::cout
			<< std::right
			<< "ID" << std::setw(3)
			<< "|" << std::setw(7)
			<< "Name" << std::setw(7)
			<< "|" << std::setw(7)
			<< "Alter" << std::setw(4)
			<< "|" << std::setw(11)
			<< "Einkommen" << std::setw(5)
			<< "|" << std::setw(5)
			<< "PLZ" << std::setw(5)
			<< "|" << std::setw(7)
			<< "PosID" << std::setw(4)
			<< "|" << std::setw(4)
			<< "RED" << std::setw(4)
			<< std::endl;
		std::cout << "----+-------------+----------+---------------+---------+----------+------------" << std::endl;

		std::queue <TreeNode*> q; // Warteschlange für Speicherung der Knoten
		q.push(this->anker);

		// Alle Knoten abarbeiten
		while (!q.empty())
		{
			TreeNode* tmp = q.front();
			q.pop(); // Dequeue

			std::cout
				<< std::right
				<< std::setw(4) << tmp->getNodeID() - 1 << "|"
				<< std::setw(13) << tmp->getName() << "|"
				<< std::setw(10) << tmp->getAlter() << "|"
				<< std::setw(15) << tmp->getEinkommen() << "|"
				<< std::setw(9) << tmp->getPLZ() << "|"
				<< std::setw(10) << tmp->getNodePosID() << "|"
				<< std::setw(4) << tmp->getRed()
				<< std::endl;

			// Kinder in die Warteschlange
			if (tmp->getLeft()) q.push(tmp->getLeft());
			if (tmp->getRight()) q.push(tmp->getRight());

		}

		this->printLevelOrder234Tree();
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::cout << "Leerer Baum." << std::endl;
	}
}

void Tree::printLevelOrder234Tree()
{
	std::cout << "Ausgabe in Levelorder als 234-Baum:" << std::endl << std::endl;

	std::queue <TreeNode*> qBlack; // Warteschlange für schwarze Knoten
	std::queue <int> qNiveau; // Das entsprechende Niveau dazu
	qBlack.push(this->anker); // Wurzel ist immer black
	qNiveau.push(0);


	int lastNiveau = 0;
	std::cout << "Niv. " << lastNiveau << ": "; // Niveau 0

	// Alle Knoten abarbeiten
	while (!qBlack.empty())
	{
		TreeNode* tmp = qBlack.front(); // Entnehme schwarzen Knoten
		qBlack.pop(); // Dequeue
		
		if (qNiveau.front() > lastNiveau)
		{
			lastNiveau = qNiveau.front();
			
			std::cout << std::endl;
			std::cout << "Niv. " << lastNiveau << ": ";

		}
		qNiveau.pop();


		std::cout << "(";

		if (tmp->getLeft())
		{
			// Prüfe ob es schwarz oder rot ist
			if (tmp->getLeft()->getRed())
			{
				std::cout << tmp->getLeft()->getNodePosID() << ",";

				if (tmp->getLeft()->getLeft() && !tmp->getLeft()->getLeft()->getRed())
				{
					qBlack.push(tmp->getLeft()->getLeft());
					qNiveau.push(this->height(tmp->getLeft()->getLeft()));
				}
				//if (tmp->getLeft()->getRight() && !tmp->getLeft()->getLeft()->getRed())
				if (tmp->getLeft()->getRight() && !tmp->getLeft()->getRight()->getRed())
				{
					qBlack.push(tmp->getLeft()->getRight());
					qNiveau.push(this->height(tmp->getLeft()->getRight()));
				}
			}
			else
			{
				qBlack.push(tmp->getLeft());
				qNiveau.push(this->height(tmp->getLeft()));
			}
		}

		std::cout << tmp->getNodePosID();
		

		if (tmp->getRight())
		{
			if (tmp->getRight()->getRed())
			{
				std::cout << "," << tmp->getRight()->getNodePosID();
				if (tmp->getRight()->getLeft() && !tmp->getRight()->getLeft()->getRed())
				{
					qBlack.push(tmp->getRight()->getLeft());
					qNiveau.push(this->height(tmp->getRight()->getLeft()));
				}
				//if (tmp->getRight()->getRight() && !tmp->getRight()->getLeft()->getRed())
				if (tmp->getRight()->getRight() && !tmp->getRight()->getRight()->getRed())
				{
					qBlack.push(tmp->getRight()->getRight());
					qNiveau.push(this->height(tmp->getRight()->getRight()));
				}
			}
			else
			{
				qBlack.push(tmp->getRight());
				qNiveau.push(this->height(tmp->getRight()));

			}
		}
		std::cout << ")";
		
	}

	std::cout << std::endl;
}

int Tree::height(TreeNode* node)
{
	int niv = 0;
	TreeNode* ptr = this->anker;
	// Traversiere solange bis wir den Knoten gefunden haben
	while (ptr != node)
	{
		if (!ptr->getRed()) niv++; // Dabei zählen wir die schwarzen Knoten um das Niveau zu ermitteln
		if (ptr->getNodePosID() < node->getNodePosID())
		{
			ptr = ptr->getRight();
		}
		else
		{
			ptr = ptr->getLeft();
		}
	}
	return niv;
}

// Suche nach dem Parent des jeweiligen Knoten
TreeNode* Tree::findParentNode(TreeNode* elternKnoten, TreeNode* kindesKnoten)
{
	if (!elternKnoten)
	{
		return nullptr;
	}
	else
	{
		if (elternKnoten->getLeft() == kindesKnoten || elternKnoten->getRight() == kindesKnoten)
		{
			return elternKnoten;
		}
		else
		{
			if (elternKnoten->getNodePosID() < kindesKnoten->getNodePosID())
				return findParentNode(elternKnoten->getRight(), kindesKnoten);
			else
				return findParentNode(elternKnoten->getLeft(), kindesKnoten);
		}
	}
}


// Prüfe ob es sich um ein 4-er Knoten handelt
bool Tree::split4Node(TreeNode* blackKnoten)
{
	if (blackKnoten->getLeft() && blackKnoten->getRight())
	{
		if (blackKnoten->getLeft()->getRed() &&
			blackKnoten->getRight()->getRed())
		{
			// Umwandlung zu zwei 2-er Knoten
			if (blackKnoten != this->anker) blackKnoten->setRed(true); // nur wenn es keine Wurzel ist
			blackKnoten->getLeft()->setRed(false);
			blackKnoten->getRight()->setRed(false);

			return true;
		}
	}
	return false;
}

bool Tree::rotateTreeRight(TreeNode* pKnoten, TreeNode* lKnoten)
{	
	// Wir können schon davon ausgehen, dass gKnoten der Großvater links vom pKnoten ist
	TreeNode* gKnoten = this->findParentNode(this->anker, pKnoten);
	//TreeNode* pKnoten = gKnoten->getLeft();
	if (gKnoten && pKnoten && pKnoten->getLeft() == lKnoten)
	{
		// Rechter Nachfolger vom pKnoten wird linker Nachfolger vom gKnoten
		gKnoten->setLeft(pKnoten->getRight());

		// Rechter Nachfolger vom pKnoten ist jetzt gKnoten
		pKnoten->setRight(gKnoten);

		TreeNode* ggKnoten = this->findParentNode(this->anker, gKnoten);
		if (ggKnoten)
		{
			// Setze Parent relation vom gKnoten zu pKnoten
			if (ggKnoten->getLeft() == gKnoten)
			{
				ggKnoten->setLeft(pKnoten);
			}
			else
			{
				ggKnoten->setRight(pKnoten);
			}
		}
		else
		{
			// gKnoten ist die Wurzel
			// pKnoten wird die neue Wurzel
			this->anker = pKnoten;
		}
		return true;
	}
	return false;
}

bool Tree::rotateTreeLeft(TreeNode* pKnoten, TreeNode* rKnoten)
{
	// Wir können schon davon ausgehen, dass gKnoten der Großvater rechts vom pKnoten ist
	TreeNode* gKnoten = this->findParentNode(this->anker, pKnoten);
	if (gKnoten && pKnoten && pKnoten->getRight() == rKnoten)
	{
		// Linker Nachfolger vom pKnoten wird rechter Nachfolger vom gKnoten
		gKnoten->setRight(pKnoten->getLeft());

		// Linker Nachfolger vom pKnoten ist jetzt gKnoten
		pKnoten->setLeft(gKnoten);


		TreeNode* ggKnoten = this->findParentNode(this->anker, gKnoten);
		if (ggKnoten)
		{
			// Setze Parent relation vom gKnoten zu pKnoten
			if (ggKnoten->getLeft() == gKnoten)
			{
				ggKnoten->setLeft(pKnoten);
			}
			else
			{
				ggKnoten->setRight(pKnoten);
			}
		}
		else
		{
			// gKnoten ist die Wurzel
			// pKnoten wird die neue Wurzel
			this->anker = pKnoten;
		}

		return true;
	}
	return false;
}

// Suche rekursiv in preorder nach Knoten mit dem Namen
void Tree::searchPreOrder(TreeNode* knoten, std::string name, bool &found)
{
	if (knoten->getName() == name)
	{
		if (!found)
		{	// mindestens 1 Fundstelle
			std::cout << "+ Fundstellen: " << std::endl;
			found = true;
		}
		knoten->print();
		found = true;
	}
	
	if (knoten->getLeft())
		this->searchPreOrder(knoten->getLeft(), name, found);
	if (knoten->getRight())
		this->searchPreOrder(knoten->getRight(), name, found);
}

// Korrigiere den Rot-Schwarz-Baum
void Tree::balanceRBTree(std::vector<TreeNode*> pfadKnoten)
{
	/* Regeln zum RB-Tree
	1. Jeder Knoten ist entweder rot oder schwarz.
	2. Jeder neu einzufügende Blattknoten ist rot.
	3. Die Kinder von einem roten Knoten sind schwarz.
	4. Es gibt keine zwei aufeinanderfolgende rote Knoten.
	5. Kriterium für Ausgeglichenheit: Für jeden Knoten k gilt: Jeder Pfad von k zu einem Blatt enth¨alt die gleiche Anzahl schwarzer Knoten.
	6. Die Wurzel ist immer schwarz.
	*/

	while (!pfadKnoten.empty())
	{
		TreeNode* bottomKnoten = pfadKnoten.back();
		TreeNode* pBottomKnoten = this->findParentNode(this->anker, bottomKnoten);
		pfadKnoten.pop_back();
		if (pBottomKnoten)
		{
			// Zwei rote Knoten folgen aufeinander
			if (pBottomKnoten->getRed() && bottomKnoten->getRed())
			{
				// Dritter Knoten zur Rotation für die Rotation - Großelternknoten
				TreeNode* gBottomKnoten = this->findParentNode(this->anker, pBottomKnoten);

				// Betrachte folgende Fälle:

				if (gBottomKnoten->getRight() == pBottomKnoten)
				{
					// 1. Fall: Rechte Kante
					if (pBottomKnoten->getRight() == bottomKnoten)
					{
						this->rotateTreeLeft(pBottomKnoten, bottomKnoten);

						pBottomKnoten->setRed(false);
						gBottomKnoten->setRed(true);
					}
					// 2. Fall: Rechts-Links-Weg
					else
					{
						// Doppelrotation
						this->rotateTreeRight(bottomKnoten, bottomKnoten->getLeft());
						this->rotateTreeLeft(bottomKnoten, pBottomKnoten);

						// Immer schön umfärben
						pBottomKnoten->setRed(true);
						gBottomKnoten->setRed(true);
						bottomKnoten->setRed(false);
					}
				}
				else
				{
					// 3. Fall: Linke Kante
					if (pBottomKnoten->getLeft() == bottomKnoten)
					{
						this->rotateTreeRight(pBottomKnoten, bottomKnoten);

						pBottomKnoten->setRed(false);
						gBottomKnoten->setRed(true);
					}
					// 4. Fall: Links-Rechts-Weg
					else
					{
						// Doppelrotation
						this->rotateTreeLeft(bottomKnoten, bottomKnoten->getRight());
						this->rotateTreeRight(bottomKnoten, pBottomKnoten);


						pBottomKnoten->setRed(true);
						gBottomKnoten->setRed(true);
						bottomKnoten->setRed(false);
					}
				}
			}

		}
		else
		{
			// Parent ist nicht da, heißt Wurzel
			bottomKnoten->setRed(false);
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
