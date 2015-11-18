#include "stack.h"

Stack::Stack()
{
	_lenght = 0;
}

void Stack::Push(std::string& newElem)
{
	// añadimos elemento
	Node* aux = new Node;
	aux->data = newElem;
	//actualizamos el puntero al dato
	if (_lenght == 0) first = aux;
	else last->next= aux;
	
	//aumentamos el tamaño de la cola
	last = aux;
	++_lenght;
}

//en las colas FIFO el primero en entrar es el primero en salir.
void Stack::Pop()
{
	Node* aux = first;		//obtenemos el primer dato en auxiliar
	first = first->next;	//sustituimos el primer dato por del segundo de la cola
	delete aux;				//eliminamos el dato de auxiliar
	--_lenght;				//disminuimos el tamaño de la cola
}


std::string Stack::Consult()
{
	return first->data;
}

bool Stack::Empty()
{
	return ( _lenght == 0 );
}

Stack::~Stack()
{
	//si quedan elementos los eliminamos
	while (_lenght != 0) Pop();
}


