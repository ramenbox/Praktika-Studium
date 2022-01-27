/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.hpp"
#include"RingNode.h"

class Ring{
	
	private:
		RingNode* anker;
		int AnzahlNodes;
	public:
		Ring();
		~Ring();

		// Getter/Setter für die Anzahl der Knoten
		void set_AnzahlNodes(int);
		int get_AnzahlNodes();

		// Methode zur Insertion eines neuen Knoten
		void addNode(std::string Beschreibung, std::string Data);
		// Methode zum Suchen nach Daten im Ringpuffer
		bool search(std::string Data);
		// Zur Ausgabe der Knoten
		void print();


		// Hilfs-Methoden
		RingNode* getFrontNode();
		void updateAge();
		void printUpFromZero(RingNode*);

		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_AnzahlNodes(Ring& r);
};
