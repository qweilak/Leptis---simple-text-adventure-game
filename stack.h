#pragma once
#include <string>

class Stack
{
private:
	
	struct Node { std::string data; struct Node* next;} *first;
	struct Node* last;
	int _lenght;

public:
	
	Stack();

	void Push(std::string&);
	void Pop();
	std::string Consult();
	bool Empty();
	virtual ~Stack();
};