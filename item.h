#pragma once
#include <string>

class Item
{
public:

public:

	struct Node { std::string name; std::string description; struct Node* next; } *first;
	
	Item();
	void Push(std::string&, std::string&);
	void Pop();
	std::string GetName();
	std::string GetDescPosN(int);
	Node* Item::ReturnNode(std::string obj);
	bool HaveItem(std::string obj);
	int Size();
	virtual ~Item();

private:
	struct Node* last;
	int lenght;
};

