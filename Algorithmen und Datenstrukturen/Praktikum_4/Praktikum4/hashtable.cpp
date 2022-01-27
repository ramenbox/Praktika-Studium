#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) {
	
	//*****************************
	// implement constructor here *
	//*****************************
	this->size = size;
	this->hashTable = new std::vector<int>(size, -1);
	this->elements = 0;
	this->collisionCount = 0;
}

HashTable::~HashTable()
{
	//****************************
	// implement destructor here *
	//****************************

	while (!this->hashTable->empty())
	{
		this->hashTable->pop_back();
		this->elements--;
	}
	this->size = 0;
	this->collisionCount = 0;
	delete this->hashTable; // Der Destruktor löscht sowieso alle Elemente aus dem Vector
}

int HashTable::hashValue(int item) {
	
	int index = -1; //dummy initialization

	//******************************************
	// implement calculation of hashindex here *
	//******************************************

	
	// Suche durch Quadratisches Sondieren einen freien Platz
	for (int i = 0; i < this->size; i++)
	{
		index = (item + i * i) % this->size;
		if (this->hashTable->at(index) != -1) // Kollision entdeckt
		{
			// h(x) = (h(x) + i * i) % N
			//index = (item + i * i) % this->size;
			this->collisionCount++;
		}
		else
		{
			return index;
		}
	}

	return index;
}

int HashTable::insert(int item) {
	
	//******************************************
	// implement insertion of new element here *
	//******************************************
	int hashIndex = this->hashValue(item);

	if (this->hashTable->at(hashIndex) == -1)
	{
		this->hashTable->at(hashIndex) = item;
		this->elements++;
	}
	return hashIndex; //dummy return
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
