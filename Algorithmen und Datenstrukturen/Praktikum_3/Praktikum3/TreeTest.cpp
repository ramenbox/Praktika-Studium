/*************************************************
* ADS Praktikum 3
* Unit-Testdatei
* Stand: 14.05.2020
*
*************************************************
* Änderungen untersagt!
*************************************************/
#include "catch.h"
#include "Tree.h"
#include "TreeNode.h"
#include <string>
#include <iostream>

using namespace std;

// Friend-Methode fuer Testroutine
TreeNode * get_anker(Tree& Tr) {
	return Tr.anker;
}

/***********************************************
 * Testroutine des Baums:
 *  - Hinzufuegen von Nodes und Suche - simple
 *  - Hinzufuegen in Baum mit Linkssrotationen
 *  - Hinzufuegen in Baum mit Rechtsrotationen
 *  - Hinzufuegen in Baum mit Rechts-Linksrotationen
 *  - Hinzufuegen mit Rechtsrotationen - Anker
 *  - Hinzufuegen mit Linkssrotationen - Anker
 *  - Hinzufuegen mit Links-Rechtsrotationen - Anker
 *  - Hinzufuegen mit Rechts-Linksrotationen - Anker
 *  - Hinzufuegen von Nodes - Erzeuge Grossbaum + Ausgabe
 *  - Getter von TreeNode - simple
 *  - Setter von TreeNode - simple
 */
TEST_CASE("Tree Testing", "[TREE]" ) {
	
	Tree * nTree = new Tree();	
	
	SECTION("Hinzufuegen von Nodes und Suche - simple"){
	
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 35, 0, 0);
		nTree->addNode("Mayer4", 26, 0, 0);
		nTree->addNode("Mayer5", 40, 0, 0);
		nTree->addNode("Mayer6", 25, 0, 0);
		nTree->addNode("Mayer7", 30, 0, 0);	
						
		REQUIRE(nTree->searchNode("Mayer") == true);
		REQUIRE(nTree->searchNode("Mayer7") == true);
		REQUIRE(nTree->searchNode("Mayer6") == true);
		REQUIRE(nTree->searchNode("Mayer5") == true);
		REQUIRE(nTree->searchNode("Mayer4") == true);
		REQUIRE(nTree->searchNode("Mayer3") == true);
		REQUIRE(nTree->searchNode("Mayer2") == true);

		REQUIRE(nTree->searchNode("Mueller") == false);
		REQUIRE(nTree->searchNode("Mayer99") == false);

		TreeNode * tanker = get_anker(*nTree);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == false);
		REQUIRE(tanker->getRight()->getRed() == true);
		REQUIRE(tanker->getRight()->getLeft()->getRed() == false);
		REQUIRE(tanker->getRight()->getRight()->getRed() == false);
		REQUIRE(tanker->getRight()->getLeft()->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getLeft()->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen in Baum mit Linkssrotationen") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 30, 0, 0);

		TreeNode * tanker = get_anker(*nTree);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRed() == true);

		nTree->addNode("Mayer4", 40, 0, 0);
		nTree->addNode("Mayer5", 45, 0, 0);

		REQUIRE(tanker->getLeft()->getRed() == false);
		REQUIRE(tanker->getRight()->getNodePosID() == 40);
		REQUIRE(tanker->getRight()->getRed() == false);
		REQUIRE(tanker->getRight()->getLeft()->getNodePosID() == 30);
		REQUIRE(tanker->getRight()->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRight()->getNodePosID() == 45);
		REQUIRE(tanker->getRight()->getRight()->getRed() == true);
	}
	
	SECTION("Hinzufuegen in Baum mit Rechtsrotationen") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 30, 0, 0);

		TreeNode * tanker = get_anker(*nTree);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRed() == true);

		nTree->addNode("Mayer4", 7, 0, 0);
		nTree->addNode("Mayer5", 3, 0, 0);

		REQUIRE(tanker->getRight()->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 7);
		REQUIRE(tanker->getLeft()->getLeft()->getNodePosID() == 3);
		REQUIRE(tanker->getLeft()->getLeft()->getRed() == true);
		REQUIRE(tanker->getLeft()->getRight()->getNodePosID() == 10);
		REQUIRE(tanker->getLeft()->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen in Baum mit Rechts-Linksrotationen") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 30, 0, 0);

		TreeNode * tanker = get_anker(*nTree);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRed() == true);

		nTree->addNode("Mayer4", 40, 0, 0);
		nTree->addNode("Mayer5", 35, 0, 0);

		REQUIRE(tanker->getLeft()->getRed() == false);
		REQUIRE(tanker->getRight()->getNodePosID() == 35);
		REQUIRE(tanker->getRight()->getRed() == false);
		REQUIRE(tanker->getRight()->getLeft()->getNodePosID() == 30);
		REQUIRE(tanker->getRight()->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRight()->getNodePosID() == 40);
		REQUIRE(tanker->getRight()->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen in Baum mit Links-Rechtsrotationen") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 30, 0, 0);

		TreeNode * tanker = get_anker(*nTree);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getRed() == true);

		nTree->addNode("Mayer4", 7, 0, 0);
		nTree->addNode("Mayer5", 8, 0, 0);

		REQUIRE(tanker->getRight()->getRed() == false);
		REQUIRE(tanker->getLeft()->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 8);
		REQUIRE(tanker->getLeft()->getLeft()->getNodePosID() == 7);
		REQUIRE(tanker->getLeft()->getLeft()->getRed() == true);
		REQUIRE(tanker->getLeft()->getRight()->getNodePosID() == 10);
		REQUIRE(tanker->getLeft()->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen mit Rechtsrotationen - Anker") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 10, 0, 0);
		nTree->addNode("Mayer3", 5, 0, 0);

		TreeNode * tanker = get_anker(*nTree);

		REQUIRE(tanker->getNodePosID() == 10);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 5);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getNodePosID() == 20);
		REQUIRE(tanker->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen mit Linksrotationen - Anker") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 30, 0, 0);
		nTree->addNode("Mayer3", 40, 0, 0);

		TreeNode * tanker = get_anker(*nTree);

		REQUIRE(tanker->getNodePosID() == 30);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 20);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getNodePosID() == 40);
		REQUIRE(tanker->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen mit Links-Rechtsrotationen - Anker") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 5, 0, 0);
		nTree->addNode("Mayer3", 10, 0, 0);

		TreeNode * tanker = get_anker(*nTree);

		REQUIRE(tanker->getNodePosID() == 10);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 5);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getNodePosID() == 20);
		REQUIRE(tanker->getRight()->getRed() == true);
	}

	SECTION("Hinzufuegen mit Rechts-Linksrotationen - Anker") {
		nTree->addNode("Mayer", 20, 0, 0);
		nTree->addNode("Mayer2", 40, 0, 0);
		nTree->addNode("Mayer3", 30, 0, 0);

		TreeNode * tanker = get_anker(*nTree);

		REQUIRE(tanker->getNodePosID() == 30);
		REQUIRE(tanker->getRed() == false);
		REQUIRE(tanker->getLeft()->getNodePosID() == 20);
		REQUIRE(tanker->getLeft()->getRed() == true);
		REQUIRE(tanker->getRight()->getNodePosID() == 40);
		REQUIRE(tanker->getRight()->getRed() == true);
	}
	
	SECTION("Hinzufuegen von Nodes - Erzeuge Grossbaum"){

		for (int i = 0; i < 124; i++ )
		{			
			string info = "Name-"+to_string(i);
			
			// Random Einkommen und PLZ
			double r = rand()+1;
			int plz = rand() + 1;
			nTree->addNode(info, 0, r, plz);
		}
		nTree->printLevelOrder();

		std::cout << "========================================" << endl;
		std::cout << "Testausgabe des Grossbaums abgeschlossen" << endl;
	} 	
}

/***********************************************
 * Testroutine des Knotens:
 *  - Einfaches pruefen der Getter und Setter in Ausführung 
 */
TEST_CASE("TreeNode Testing", "[TREENODE]" ) {
		
	Tree * smallTree = new Tree();
	smallTree->addNode("Scholl", 20, 0, 0);
	TreeNode * ref = get_anker(*smallTree);

	SECTION("Getter von TreeNode - simple") {

		REQUIRE(ref->getName() == "Scholl");
		REQUIRE(ref->getAlter() == 20);
		REQUIRE(ref->getEinkommen() == 0);
		REQUIRE(ref->getLeft() == nullptr);
		REQUIRE(ref->getRight() == nullptr);
		REQUIRE(ref->getNodeID() == 1);
		REQUIRE(ref->getNodePosID() == 20);
		REQUIRE(ref->getPLZ() == 0);
	}

	SECTION("Setter von TreeNode - simple") {
		
		ref->setAlter(22);
		REQUIRE(ref->getAlter() == 22);

		ref->setEinkommen(1000);
		REQUIRE(ref->getEinkommen() == 1000);
		
		ref->setLeft(nullptr);
		REQUIRE(ref->getLeft() == nullptr);

		ref->setRight(nullptr);
		REQUIRE(ref->getRight() == nullptr);

		ref->setName("Kaiser");
		REQUIRE(ref->getName() == "Kaiser");

		ref->setPLZ(1000);
		REQUIRE(ref->getPLZ() == 1000);
			
	}	
	delete ref;
	delete smallTree;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// http://www.hashemall.com/
// Zeile 1-282 hat den SHA 256 Hashwert: E613C60CFA5C987DA68179A692EB2BEDD824A6206F933578313917C3F50A88B1
