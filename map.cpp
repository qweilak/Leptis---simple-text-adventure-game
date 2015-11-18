#include "map.h"
#include "constants.h"
#include <Windows.h>
#include <iostream>

Map::Map()
{
	_arrayOfRooms[1] = { "Entrada al Colegio",	"Bienvenido a la escuela de Leptis. Este edificio ha sido un centro de formación básica para todos aquellos que han decidico aventurares por este mundo." };
	_arrayOfRooms[2] = { "Sala de Lectura",		"Te encuentras en una amplia sala repleta de estanterías. En cada una de ellas se ven apilados un sinfín de pergaminos escritos en todas las lenguas del mar mediterraneo." };
	_arrayOfRooms[3] = { "Pasillo",				"Es difícil caminar por este pasillo repleto de aperos, armaduras, armas e incluso objetos extraños. Aunque tu imaginación te dice que todos ellos sirven para matar o protegerse." };
	_arrayOfRooms[4] = { "Sala de prácticas",	"Sala de entrenamiento para aprendices y noviciosn." };
	_arrayOfRooms[5] = { "Entrada a la Arena",	"Puedes ver una amplia zona donde otros los aprendices luchaban contra bestias para mejorar sus habilidades." };
	_arrayOfRooms[6] = { "Burladero",			"En esta esquina es el lugar ideal para descansar y reponerse. Unos tablones de madera permiten refugiarte de las bestias que hubiera en la arena." };
	_arrayOfRooms[7] = { "Arena",				"El suelo compacto muestra huellas de combates entre bestias y alumnos." };
	_arrayOfRooms[0] = { "No Room", "No Desc" };
/*
	_area.code =  { { 1, 2, 3, 0, 0 };	// 1 "Entrada al Colegio", 2 "Sala de Lectura", 3 "Pasillo"
					{ 0, 0, 4, 0, 0 },	// 4 "Sala de prácticas", 5 "Entrada a la Arena" ,6 "Burladero"
					{ 6, 7, 105, 7, 6 },	// 7 "Arena", 0 "No Room"
					{ 7, 7, 7, 7, 7 },
					{ 6, 7, 7, 7, 6 } };
	code + 100 = sala cerrada;
*/
	_area[0][0].code = 1; _area[0][1].code = 2; _area[0][2].code = 3;_area[0][3].code = _area[0][4].code = 0;
	_area[1][0].code = _area[1][1].code = _area[1][3].code = _area[1][4].code = 0; _area[1][2].code = 4;
	_area[2][0].code = _area[2][4].code = 6; _area[2][1].code = _area[2][3].code = 7; _area[2][2].code = 105;
	_area[3][0].code = _area[3][1].code = _area[3][2].code = _area[3][3].code = _area[3][4].code = 7;
	_area[4][0].code = _area[4][4].code = 6; _area[4][1].code = _area[4][2].code = _area[4][3].code = 7;

	_area[0][0].itemslist.Push((std::string)"bota", (std::string)"Una pequeña bota de agua");
	_area[4][4].itemslist.Push((std::string)"espada", (std::string)"Una espada de madera");
	
}



Map::~Map()
{
}

void Map::ShowRoom(const short _lat, const short _long)
{
	colortext(WHITE);
	printf(Read_from_Room(_arrayOfRooms[_area[_lat][_long].code].title));
	colortext(LIGHTGREY);
	printf(Read_from_Room( _arrayOfRooms[_area[_lat][_long].code].description));
	printf(ITEMS_IN_ROOM);
	if (_area[_lat][_long].itemslist.Size() > 0)
		for (int i = 0; i < _area[_lat][_long].itemslist.Size(); ++i)
			printf(Show_Item(_area[_lat][_long].itemslist.GetDescPosN(i).c_str()));
}

Item::Node* Map::GetFromMap(const short _lat, const short _long, std::string obj)
{
	if (_area[_lat][_long].itemslist.Size() <= 0)
		return nullptr;

	return _area[_lat][_long].itemslist.ReturnNode(obj);

}

void Map::DropToMap(const short _lat, const short _long, Item::Node* obj)
{
	_area[_lat][_long].itemslist.Push(obj->name, obj->description);	
}


void Map::ShowExits(const short _lat, const short _long)
{
	colortext(YELLOW);
	printf(EXITS_LOWER);
	if (CheckN(_lat, _long) > 0)
	{
		printf(NORTH_LOWER);
		if (CheckN(_lat, _long) > 100)
			printf(CLOSED);
	}
	if (CheckS(_lat, _long))
	{
		printf(SOUTH_LOWER);
		if (CheckS(_lat, _long) > 100)
			printf(CLOSED);
	}
	if (CheckE(_lat, _long)) 
	{
		printf(EAST_LOWER);	
		if (CheckE(_lat, _long) > 100)
			printf(CLOSED);
	}
	if (CheckW(_lat, _long))
	{
		printf(WEST_LOWER);
		if (CheckW(_lat, _long) > 100)
			printf(CLOSED);
	}

	printf("\n");

	colortext(LIGHTGREY);
}

short Map::CheckW(const short _lat, const short _long)
{
	if (_long - 1 >= 0)
		if (_area[_lat][_long - 1].code != 0)
			return _area[_lat][_long - 1].code;
	return 0;
}

short Map::CheckE(const short _lat, const short _long)
{
	if (_long + 1 <= 4)
		if (_area[_lat][_long + 1].code != 0)
			return _area[_lat][_long + 1].code;
	return 0;
}

short Map::CheckN(const short _lat, const short _long)
{
	if (_lat - 1 >= 0)
		if (_area[_lat - 1][_long].code != 0)
			return _area[_lat - 1][_long].code;
	return 0;
}

short Map::CheckS(const short _lat, const short _long)
{
	if (_lat + 1 <= 4)
		if (_area[_lat + 1][_long].code != 0)
			return _area[_lat + 1][_long].code;
	return 0;
}

void Map::OpenDoor(const short _lat, const short _long)
{
	if (_area[_lat][_long].code > 100)
	{
		if (_lat > 0 && _lat < 5)
			if (_long > 0 && _long < 5)
			{
				_area[_lat][_long].code = _area[_lat][_long].code - 100;
				printf(OPENED_DOOR);
			}

	}
	else printf(NO_DOOR);
}