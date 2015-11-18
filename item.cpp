#pragma once 
#include "item.h"

Item::Item()
{
	lenght = 0;
}

void Item::Push(std::string& name, std::string& desc)
{
	// añadimos elemento
	Node* aux = new Node;
	aux->name = name;
	aux->description = desc;
	//actualizamos el puntero al dato
	if (lenght == 0) first = aux;
	else last->next = aux;

	//aumentamos el tamaño de la cola
	last = aux;
	++lenght;
}

//en las colas FIFO el primero en entrar es el primero en salir.
void Item::Pop()
{
	Node* aux = first;		//obtenemos el primer dato en auxiliar
	first = first->next;	//sustituimos el primer dato por del segundo de la cola
	delete aux;				//eliminamos el dato de auxiliar
	--lenght;				//disminuimos el tamaño de la cola
}


std::string Item::GetName()
{
	return first->name;
}

std::string Item::GetDescPosN(int i)
{
	Node* aux;
	aux = first;
	for (int element = 0; element < i; ++element)
		aux = aux->next;
	return aux->description;
}

Item::Node* Item::ReturnNode(std::string obj)
{
	Node* aux;
	Node* prev;
	prev = first;
	aux = first;
	int i = 0;
	if (first->name == obj)
		first = first->next;
	else
	{
		while ((i < lenght) && (aux->name != obj))
		{
			i++;
			prev = aux;
			aux = aux->next;
		}
		if (last->name == obj)
		{
			aux = last;
			last = prev;
		}else
		if ((i == lenght) && (last->name != obj)) return nullptr;
		else prev->next = aux->next;	
		
	}
	--lenght;
	return aux;
}

bool Item::HaveItem(std::string obj)
{
	if (last->name == obj)
		return 1;
	Node* aux;
	aux = first;
	int i = 0;
	while (i < lenght && aux->name != obj)
	{	
		i++;
		aux = aux->next;
	}
	
	return 0;
}

int Item::Size()
{
	return lenght;
}

Item::~Item()
{
	//si quedan elementos los eliminamos
	while (lenght != 0) Pop();
}
