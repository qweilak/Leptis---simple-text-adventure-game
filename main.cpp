#pragma once
#include <conio.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include "stack.h"
#include "constants.h"
#include "map.h"
#include "item.h"
#include "player.h"

// variables
Stack stackCommands;
Player myPlayer(0,0);
Map myMap;
Container bag;
loopState gameState;


//funciones
void Init(clock_t &tLast);
void Update(clock_t &tLast, short &charIndex, bool &newWord, char(&command)[MAX_CHARATERS_PER_LINE]);

inline void Prompt() { printf("\n>"); };
inline int Compare(const std::string a, const std::string b) { return !strncmp(a.c_str(), b.c_str(), strlen(b.c_str())); };

const char GetCharacter(const bool b);
void ShowCommands();
const string_code Hashit(std::string const& inString);
void NewRoom();
std::string GetWord(const char[MAX_CHARATERS_PER_LINE]);
std::string CutFirstWord(const char[MAX_CHARATERS_PER_LINE]);

int main()
{
	//no son globales
	clock_t tLast;	
	short charI = 0;
	bool newW = 0;
	char command[MAX_CHARATERS_PER_LINE];

	Init(tLast);
	
	while (gameState == loop)
	{
		Update(tLast, charI, newW , command);
	}
	colortext(WHITE);
	printf(BYEBYE);
	system("pause");
	return 0;
}

void Init(clock_t &tLast)
{
	setlocale(LC_CTYPE, "Spanish");		//Set acentos
	tLast = clock();
	
	bag.SetName(BAG);
	bag.SetDescription(BAG_DESC);
	bag.SetLatitude(0);
	bag.SetLongitude(0);
	bag.SetState('s');
	bag.ilist.Push((std::string)"llave", (std::string)"Una llave de acero oxidada"); //objeto no lo pongo en las strings de constants.h
	colortext(YELLOW);
	printf(MISSION);
	NewRoom();
	Prompt();
	gameState =  loop;
}

const char GetCharacter(const bool b)
{
	//si no hay nueva palabra escuchamos TIMEOUT milisegundos el teclado
	if (b == 0)
	{
		for (short timeout = TIMEOUT; timeout > 0; --timeout)
		{
			if (_kbhit())
			{
				return getchar();
			}
		}
		return NULL;
	}
	return getchar();
}

std::string Upcase(const std::string& w)
{
	char stringUpcase[MAX_CHARATERS_PER_LINE];

	int i = 0;
	while(i < w.length())
	{
		stringUpcase[i] = toupper(w[i]);
		++i;
	}
	stringUpcase[i] = 0;
	return stringUpcase;
}

void Update(clock_t &tLast, short &charIndex, bool &newWord, char(&command)[MAX_CHARATERS_PER_LINE])
{

	command[charIndex] = GetCharacter(newWord);					//escuchamos la entrada de datos con un timeout para poder dedicar tiempo a los calculos posteriores

																//verificamos que tenemos caracter leido o nueva palabra empezada
	if (command[charIndex] != NULL || newWord != 0)
	{
		if (newWord == 0) { newWord = 1; }						//ponemos a true el boleano de palabra

																//cuando pulse enter el jugador, almacenamos la palabra en el stack y reseteamos el indice de nuestra palabra asi como el boleano 
																//en caso contrario aumentamos el indice para obtener una nueva letra

		if (command[charIndex] == '\n')
		{
			command[charIndex] = 0;
			if (charIndex > 0)					//si tan solo pulsa enter no necesitamos almacenarlo en la pila
			{
				newWord = 0;
				stackCommands.Push((std::string) command);
				command[0] = 0;
			}
			else
			{
				Prompt();
			}
			charIndex = 0;
		}
		else
		{
			++charIndex;
		}
	}

	//tratamiento acciones o comandos
	//Si la pila no esta vacia y el delay se cumple ejecutamos una nueva instruccion
	if (!stackCommands.Empty() && (clock() - tLast) > DELAY_BETWEEN_COMMANDS)
	{
		//La palabra reservada para ejecutar 'salir del juego' es especial ya que requiere de verificación. 
		if (LEAVE == Upcase(stackCommands.Consult()))
		{
			char a[MAX_CHARATERS_PER_LINE];	//para no obtener datos de la pila definios una nueva variable
			a[0] = 0;
			do				//para salir hay que verificar antes
			{
				printf(LEAVE_Q);
				scanf_s("%s", a, _countof(a));
			} while (!Compare(YES, Upcase(a)) && !Compare(NO, Upcase(a)));

			if (Compare(YES, Upcase(a)))  gameState = endLoop;
			else
			{
				Prompt();
				stackCommands.Pop();
			}
		}
		else
		ShowCommands();
		tLast = clock();
	}
}

void ShowCommands()
{
	//acciones de palabras simples
	std::string action = stackCommands.Consult().c_str();
	int i = 0;
	char result = 's';
	switch (Hashit(Upcase(action)))
	{
	case	ayuda:

			printf(HELP_LIST);
			colortext(WHITE); printf(LEAVE); colortext(LIGHTGREY); printf(HELP_LEAVE);
			colortext(WHITE); printf(OPEN_DOOR); colortext(LIGHTGREY); printf(HELP_OPEN_DOOR);
			colortext(WHITE); printf(CLEAR_SCREEN); colortext(LIGHTGREY); printf(HELP_CLEAR_SCREEN);
			colortext(WHITE); printf(PICKUP); colortext(LIGHTGREY); printf(HELP_PICKUP);
			colortext(WHITE); printf(EAST); colortext(LIGHTGREY); printf(HELP_EAST);
			colortext(WHITE); printf(PUT_IN_BAG); colortext(LIGHTGREY); printf(HELP_PUT_IN_BAG);
			colortext(WHITE); printf(INV); colortext(LIGHTGREY); printf(HELP_INV);
			colortext(WHITE); printf(LOOK); colortext(LIGHTGREY); printf(HELP_LOOK);
			colortext(WHITE); printf(NORTH); colortext(LIGHTGREY); printf(HELP_NORTH);
			colortext(WHITE); printf(WEST); colortext(LIGHTGREY); printf(HELP_WEST);
			colortext(WHITE); printf(EXITS); colortext(LIGHTGREY); printf(HELP_EXITS);
			colortext(WHITE); printf(DROP); colortext(LIGHTGREY); printf(HELP_DROP);
			colortext(WHITE); printf(GET_FROM_BAG); colortext(LIGHTGREY); printf(GET_FROM_BAG);
			colortext(WHITE); printf(SOUTH); colortext(LIGHTGREY); printf(HELP_SOUTH);
			
			break;
	case	mirar:
		NewRoom();
		break;
	case	norte:
		if (myMap.CheckN(myPlayer.GetLatitude(), myPlayer.GetLongitude()) > 0 && myMap.CheckN(myPlayer.GetLatitude(), myPlayer.GetLongitude()) < 100)
		{
			myPlayer.SetLatitude(myPlayer.GetLatitude() - 1);
			NewRoom();
		}
		else printf(NO_EXITS);
		break;
	case	sur:
		if (myMap.CheckS(myPlayer.GetLatitude(), myPlayer.GetLongitude())> 0 && myMap.CheckS(myPlayer.GetLatitude(), myPlayer.GetLongitude()) < 100)
		{
			myPlayer.SetLatitude(myPlayer.GetLatitude() + 1);
			NewRoom();
		}
		else printf(NO_EXITS);
		break;
	case	este:
		if (myMap.CheckE(myPlayer.GetLatitude(), myPlayer.GetLongitude())> 0 && myMap.CheckE(myPlayer.GetLatitude(), myPlayer.GetLongitude()) < 100)
		{
			myPlayer.SetLongitude(myPlayer.GetLongitude() + 1);
			NewRoom();
		}
		else printf(NO_EXITS);
		break;
	case	oeste:

		if (myMap.CheckW(myPlayer.GetLatitude(), myPlayer.GetLongitude())> 0 && myMap.CheckW(myPlayer.GetLatitude(), myPlayer.GetLongitude()) < 100)
		{
			myPlayer.SetLongitude(myPlayer.GetLongitude() - 1);
			NewRoom();
		}
		else printf(NO_EXITS);
		break;
	case	salidas:
		myMap.ShowExits(myPlayer.GetLatitude(), myPlayer.GetLongitude());
		break;
	case	cls:
		system("cls");
		break;
	case	inventario:
		printf(INVENTORY);
		if (bag.GetState() == 's')
			printf(Show_Item(bag.GetDescription().c_str()));

		if (myPlayer.inventory.Size() > 0)
		{
				for (int i = 0; i < myPlayer.inventory.Size(); ++i)
					printf(Show_Item(myPlayer.inventory.GetDescPosN(i).c_str()));
		}
			else
				if ( bag.GetState() != 's' ) printf( NOTHING_TO_SHOW );
		break;
	default:
		result = 'n';
		break;
	}
	//acciones de 2 palabras
	action = GetWord(stackCommands.Consult().c_str());
	Item::Node *tmp;
	switch (Hashit(Upcase(action)))
	{
	case	coger:
		action = CutFirstWord(stackCommands.Consult().c_str());
		action = GetWord(action.c_str());
	
		if (action == BAG)
		{
			bag.ToInventory(myPlayer.GetLatitude(), myPlayer.GetLongitude());
		}
		else
		{
			tmp = myMap.GetFromMap(myPlayer.GetLatitude(), myPlayer.GetLongitude(), action);
			if (tmp != nullptr)
			{
				printf(Pick(action.c_str()));
				myPlayer.inventory.Push(tmp->name, tmp->description);
				if (tmp->name == "espada") // habitacion - El burladero de la esquina sur este.
				{
					colortext(YELLOW);
					printf(GAME_OVER);
					gameState = endLoop;
					return;
				}
				delete tmp;
			}
			else
			{
				printf(Not_found(action.c_str()));
			}
		}
		break;
	case	tirar:
		action = CutFirstWord(stackCommands.Consult().c_str());
		action = GetWord(action.c_str());

		if (action == BAG)
		{
			bag.DropItem(myPlayer.GetLatitude(), myPlayer.GetLongitude());
	
		}
		else
		{
			tmp = myPlayer.GetInventory(action);
			if (tmp != nullptr)
			{
				printf(Drop_Item(action.c_str()));
				myMap.DropToMap(myPlayer.GetLatitude(), myPlayer.GetLongitude(), tmp);
				delete tmp;
			}
			else
			{
				printf(Inventory_void(action.c_str()));
			}
		}
		break;
	case guardar:

		if (bag.GetState() != 's')
			printf(NO_BAG);
		else
		{
			action = CutFirstWord(stackCommands.Consult().c_str());
			action = GetWord(action.c_str());

			tmp = myPlayer.GetInventory(action);
			if (tmp != nullptr)
			{
				printf(Put_in_bag(action.c_str()));
				bag.ilist.Push(tmp->name, tmp->description);
				delete tmp;
			}
			else
			{
				if (action == BAG) printf(BAG_IN_BAG);
				else printf(Inventory_void(action.c_str()));
			}
		}
		break; case sacar:

			if (bag.GetState() != 's')
				printf(NO_BAG);
			else
			{
				action = CutFirstWord(stackCommands.Consult().c_str());
				action = GetWord(action.c_str());
				tmp = bag.GetFromContainer(action);
				if (tmp != nullptr)
				{
					printf(Pick(action.c_str()));
					myPlayer.inventory.Push(tmp->name, tmp->description);
					delete tmp;
				}
				else
				{
					printf(Not_In_bag(action.c_str()));
				}
			}
			break;
		case abrir:
			if (myPlayer.inventory.Size() > 0)
				if (myPlayer.inventory.HaveItem("llave"))
				{
					action = CutFirstWord(stackCommands.Consult().c_str());
					action = GetWord(action.c_str());
					switch ((Hashit(Upcase(action))))
					{
					case sur:
						myMap.OpenDoor(myPlayer.GetLatitude() + 1 , myPlayer.GetLongitude());
						break;
					case norte:
						myMap.OpenDoor(myPlayer.GetLatitude() - 1, myPlayer.GetLongitude());
						break;
					case este:
						myMap.OpenDoor(myPlayer.GetLatitude(), myPlayer.GetLongitude() + 1);
						break;
					case oeste:
						myMap.OpenDoor(myPlayer.GetLatitude(), myPlayer.GetLongitude() - 1);
						break;
					default:
						break;
					}
				}
				else
					printf(Inventory_void("llave"));
			else
					printf(Inventory_void("llave"));
				break;
		default:
			if (result == 'n')
				printf(NO_ACTION);
		break;
	}

	Prompt();
	stackCommands.Pop();
}

const string_code Hashit(std::string const& inString) {

	if (CLEAR_SCREEN == inString) return cls; //cls es cls no es correcto recortar esta palabra sino molesta al jugador se molesta.
	if (Compare(NORTH, inString)) return norte;
	if (Compare(SOUTH, inString)) return sur;
	if (Compare(EAST, inString)) return este;
	if (Compare(WEST, inString)) return oeste;
	if (Compare(EXITS, inString)) return salidas;
	if (Compare(INV, inString)) return inventario;
	if (Compare(PICKUP, inString)) return coger;
	if (Compare(LOOK, inString)) return mirar;
	if (Compare(DROP, inString)) return tirar;
	if (Compare(PUT_IN_BAG, inString)) return guardar;
	if (Compare(GET_FROM_BAG, inString)) return sacar;
	if (Compare(OPEN_DOOR, inString)) return abrir;
	if (Compare(HELP, inString)) return ayuda;
	if (Compare(AYUDA, inString)) return ayuda;
	return enull;
}

std::string GetWord(const char s[MAX_CHARATERS_PER_LINE])
{
	char myWord[MAX_CHARATERS_PER_LINE];
	int i = myWord[0] = 0;
	while (s[i]!= BLANK_SAPACE && s[i] != NULL)
	{
		myWord[i] = s[i];
		++i;
	}
	myWord[i] = 0;
	return myWord;
}
std::string CutFirstWord(const char s[MAX_CHARATERS_PER_LINE])
{
	char myWord[MAX_CHARATERS_PER_LINE];
	int i = myWord[0] = 0;
	//saltamos primera palabra
	while (s[i] != BLANK_SAPACE && s[i] != NULL) ++i;
	//saltamos espacios
	while (s[i] == BLANK_SAPACE && s[i] != NULL)	++i;
	
	int j = 0;
	//guardamos el resto
	do
	{
		myWord[j] = s[i];
		++j;
		++i;
	} while (s[i] != NULL);
	myWord[j] = 0;
	return myWord;
}

void NewRoom() 
{
	myMap.ShowRoom(myPlayer.GetLatitude(), myPlayer.GetLongitude());
	bag.ShowInRoom(myPlayer.GetLatitude(),myPlayer.GetLongitude()); // contenedor.
	myMap.ShowExits(myPlayer.GetLatitude(), myPlayer.GetLongitude());
}