#pragma once
#include <string>
#include "item.h"

class Container
{
public:

	Container();
	~Container();

	void ShowInRoom(const short _lat, const short _long);
	void ToInventory(const short lat, const short lon);

	Item::Node * GetFromContainer(std::string obj);
	void DropItem(const short lat, const short lon);

	Item ilist;
	char state; // 'g' grounded (en el suelo); 'i' inventory (en el inventario);

	void SetLongitude(short const lon) { _myLongitude = lon; };
	const short GetLongitude() { return _myLongitude; };
	void SetLatitude(short const lat) { _myLatitude = lat; };
	const short GetLatitude() { return _myLatitude; };
	void SetName(const std::string n) { _name = n; };
	const std::string GetName() { return _name; };	
	void SetDescription(const std::string d) { _desc = d; };
	const std::string GetDescription() { return _desc; };
	void SetState(char s) { _state = s; };
	char GetState() { return _state; };

private:

	short _myLongitude, _myLatitude;
	std::string _name;
	std::string _desc;
	//_state codes 'g' item contenedor en el suelo, 'i' item contenedor en el inventario
	char _state; 
};

