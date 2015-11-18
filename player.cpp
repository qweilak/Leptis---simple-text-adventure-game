#include "player.h"


Player::Player(short const _lat, short const _long)
{
	_myLongitude = _long;
	_myLatitude = _lat;
}

Item::Node* Player::GetInventory(std::string obj)
{
	if (inventory.Size() <= 0)
		return nullptr;

	return inventory.ReturnNode(obj);
}

Player::~Player()
{
}
