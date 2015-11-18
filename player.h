#pragma once
#include "item.h"
class Player
{
public:
	Player(short const _lat, short const _long);
	~Player();

	void SetLongitude(short const _long) { _myLongitude = _long; };
	short GetLongitude() { return _myLongitude; };
	void SetLatitude(short const _lat) { _myLatitude = _lat; };
	short GetLatitude() { return _myLatitude; };
	Item::Node * GetInventory(std::string obj);
	Item inventory;

private:

	short _myLongitude, _myLatitude;
};

