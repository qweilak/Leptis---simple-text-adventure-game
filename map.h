#pragma once
#include "item.h"
#include "container.h"
#include "constants.h"

class Map
{
private:

	typedef struct { char title[25]; char description[MAX_CHARATERS_PER_LINE];} room;
	typedef struct { short code; Item itemslist; } arearoom;

	arearoom _area[5][5];
	room _arrayOfRooms[8];

public:

	Map();
	~Map();

	void ShowRoom(const short _lat, const short _long);
	Item::Node* GetFromMap(const short _lat, const short _long, std::string obj);
	void  DropToMap(const short _lat, const short _long, Item::Node* obj);
	void ShowExits(const short _lat, const short _long);
	short CheckW(const short _lat, const short _long);
	short CheckE(const short _lat, const short _long);
	short CheckN(const short _lat, const short _long);
	short CheckS(const short _lat, const short _long);

	void OpenDoor(const short _lat, const short _long);


};

