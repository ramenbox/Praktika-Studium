/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>


Ring::Ring()
{
	this->anker = nullptr; // Zu Beginn ist der Ring noch leer
	this->AnzahlNodes = 0;
}

Ring::~Ring()
{
	//TODO: Muss alle Knoten löschen
	if (this->anker)
	{
		RingNode* current = this->anker->getNext();
		while (current != this->anker)
		{
			// Vorheriger Knoten wird gespeichert
			RingNode* delKnoten = current;

			current = current->getNext();
			
			// Lösche den vorherigen Knoten
			delete delKnoten;
		}
		// Lösche den Anker
		delete current;
		this->AnzahlNodes = 0;
	}
}

void Ring::set_AnzahlNodes(int anzahl_nodes)
{
	this->AnzahlNodes = anzahl_nodes;
}

int Ring::get_AnzahlNodes()
{
	return this->AnzahlNodes;
}

void Ring::addNode(std::string Beschreibung, std::string Data)
{
	// Einfügen eines neuen Knoten

	// Neuer Knoten ist unser aktueller Knoten
	// und zeigt immer auf den ältesten Knoten.
	RingNode* neuerKnoten = new RingNode(0, Beschreibung, Data);


	if (this->anker)
	{

		RingNode* oldestNode = this->anker->getNext();
		// Prüfe ob max. 6 Nodes vorhanden sind
		if (oldestNode->getAge() == 5 && this->AnzahlNodes == 6)
		{
			//TODO: Überschreibe ältester Knoten (Knoten komplett)
			
			// Neuer ältester Knoten wird aktualisiert
			neuerKnoten->setNext(oldestNode->getNext());
			// Der aktueller Knoten wird bis nach vorne geschoben
			this->getFrontNode()->setNext(this->anker);
			this->anker->setNext(neuerKnoten);
			

			this->anker = neuerKnoten;
			delete oldestNode;

			this->AnzahlNodes--;

			this->updateAge();
		}
		else
		{
			// Ringpuffer wächst dynamisch

			neuerKnoten->setNext(oldestNode);
			// Der Knoten mit OldAge = 1 soll auf den Knoten
			// mit OldAge = 0 zeigen.
			this->getFrontNode()->setNext(this->anker);
			this->anker->setNext(neuerKnoten);

			// Neuer aktueller Knoten
			this->anker = neuerKnoten;

			// Aktualisiere die OldAge information aller Knoten
			this->updateAge();
			
		}
	}
	else
	{
		// Ringpuffer leer
		this->anker = neuerKnoten;
		// Da wir dann nur einen Knoten im Ringpuffer haben
		// zeigt er auf sich selber
		this->anker->setNext(this->anker);
	}

	this->AnzahlNodes++;
}

bool Ring::search(std::string Data)
{
	bool foundNode = false;

	RingNode* current = this->anker->getNext();
	// Durchlaufe den Ring
	while (current != this->anker)
	{
		if (current->getData() == Data)
		{
			foundNode = true;
			break;
		}
		current = current->getNext();
	}
	// Für den aktuellen Knoten
	if (foundNode || current->getData() == Data)
	{
		std::cout << "+ Gefunden in Backup: "
			<< "OldAge " << current->getAge() << ", "
			<< "Beschreibung: " << current->getDescription() << ", "
			<< "Daten: " << current->getData()
			<< std::endl;
		return true;
	}
	// TODO: Better way to search - vielleicht mit AnzahlNodes
	return false;
}

void Ring::printUpFromZero(RingNode* current)
{
	// Rekursives Ausgeben der Datensätze

	if (current != this->anker) // Keine endlose Rekursion
		printUpFromZero(current->getNext());

	std::cout << "OldAge: " << current->getAge() << ", "
		<< "Descr: " << current->getDescription() << ", "
		<< "Data " << current->getData()
		<< std::endl
		<< "--------------------------------------------"
		<< std::endl;
}


void Ring::print()
{
	// Ringpuffer darf nicht leer sein
	if (this->anker)
		printUpFromZero(this->anker->getNext());
}

RingNode* Ring::getFrontNode()
{
	RingNode* frontNode = this->anker->getNext();
	// Wir benötigen den "Ersten" Knoten
	while (frontNode->getNext() != this->anker)
	{
		// Einen Knoten weiter
		frontNode = frontNode->getNext();
	}
	return frontNode;
}

void Ring::updateAge()
{
	RingNode* current = this->anker->getNext();
	// Ignoriere den aktuellsten Knoten bzw. OldAge = 0
	int i = 0;
	while (current != this->anker)
	{
		current->setAge(
			this->AnzahlNodes - i++
		);

		current = current->getNext();
	}
}
