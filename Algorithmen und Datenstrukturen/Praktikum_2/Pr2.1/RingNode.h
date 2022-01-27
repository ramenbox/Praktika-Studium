/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	std::string SymbolicData;
	std::string Description;
	RingNode* next;
	int OldAge;

public:
	RingNode();
	RingNode(int, std::string, std::string);

	~RingNode();

	// Methoden zum Setter/Getter von Next-Zeiger
	void setNext(RingNode*);
	RingNode* getNext();

	// Setter/Getter f�r Knotendaten
	void setData(std::string);
	std::string getData();

	// Setter/Getter f�r Knotenbeschreibung
	void setDescription(std::string);
	std::string getDescription();

	// Setter/Getter f�r OldAge
	void setAge(int);
	int getAge();
};
