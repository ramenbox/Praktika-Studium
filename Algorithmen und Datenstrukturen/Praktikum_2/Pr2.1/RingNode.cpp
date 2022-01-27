/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"

RingNode::RingNode()
{
	this->Description = "";
	this->SymbolicData = "";
	this->next = nullptr;
	this->OldAge = 0;
}

RingNode::RingNode(int age, std::string desc, std::string d)
{
	this->Description = desc;
	this->SymbolicData = d;
	this->next = nullptr;
	this->OldAge = age;
}

RingNode::~RingNode()
{
}

void RingNode::setNext(RingNode* n)
{
	this->next = n;
}

RingNode* RingNode::getNext()
{
	return this->next;
}

void RingNode::setData(std::string d)
{
	this->SymbolicData = d;
}

std::string RingNode::getData()
{
	return this->SymbolicData;
}

void RingNode::setDescription(std::string desc)
{
	this->Description = desc;
}

std::string RingNode::getDescription()
{
	return this->Description;
}

void RingNode::setAge(int age)
{
	this->OldAge = age;
}

int RingNode::getAge()
{
	return this->OldAge;
}
