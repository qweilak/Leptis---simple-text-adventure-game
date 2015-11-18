#pragma once

// Values
#define TIMEOUT 100
#define DELAY_BETWEEN_COMMANDS 500  //razonable entre 500 y 1000 ms
#define MAX_CHARATERS_PER_LINE 256
#define BLANK_SAPACE ' '
#define YES "SI"
#define NO "NO"

#define EXITS_LOWER "salidas: "
#define NORTH_LOWER "norte "
#define SOUTH_LOWER "sur "
#define EAST_LOWER "este "
#define WEST_LOWER "oeste "
#define CLOSED "(cerrado)"

//actions & commands
#define CLEAR_SCREEN "CLS"
#define NORTH "NORTE"
#define SOUTH "SUR"
#define EAST "ESTE"
#define WEST "OESTE"
#define EXITS "SALIDAS"
#define INV "INVENTARIO"
#define PICKUP "COGER"
#define LOOK "MIRAR"
#define DROP "TIRAR"
#define PUT_IN_BAG "GUARDAR"
#define GET_FROM_BAG "SACAR"
#define OPEN_DOOR "ABRIR"
#define HELP "HELP"
#define AYUDA "AYUDA"
#define LEAVE "ABANDONAR"

// enums
enum string_code { norte, sur, este, oeste, salidas, cls, enull, inventario, coger, mirar, tirar, guardar, sacar, abrir, ayuda};
enum loopState { loop, endLoop };

// colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

//Strings 
#define MISSION "Encuentra la espada de madera para terminar el juego.\n"
#define BYEBYE "\nQue la suerte te sonría...\n\n\n"
#define GAME_OVER "Felicidades, encontraste la espada!!\n\n"
#define BAG "bolsa"
#define NO_EXITS  "No hay salida en esa dirección.\n"
#define NO_ACTION "No se reconoce esa acción!\n"
#define LEAVE_Q   "\nDeseas salir? Si(S/s) / No(N/n)...\n"
#define NO_BAG "No tienes una bolsa"
#define INVENTORY "En tu inventario tienes:\n\n"
#define BAG_IN_BAG "Te quedas aturdido pensando en agujeros negros."
#define BAG_DESC "Una pequeña bolsa"
#define NOTHING_TO_SHOW " Vacio.\n\n"
#define ITEMS_IN_ROOM "\nAquí puedes ver:\n\n"
#define NO_DOOR "No hay una puerta ahí."
#define OPENED_DOOR "Al girar la llave y abrir la puerta las bisagras anuncian con un chirrido que has tenido éxito."

#define HELP_LIST "\nListado de acciones:\n\n"
#define HELP_LEAVE "..........:Salir del juego.\n"
#define HELP_OPEN_DOOR " <Dirección>..:Abrir puertas.\n"
#define HELP_CLEAR_SCREEN "................:Borra la pantalla.\n"
#define HELP_PICKUP " <Objeto>.....:Coger un objeto del suelo.\n"
#define HELP_EAST "...............:Desplazarse a la habitación del este.\n"
#define HELP_PUT_IN_BAG " <Objeto>...:Guardar un objeto del inventario en la bolsa.\n"
#define HELP_INV ".........:Ver el inventario.\n"
#define HELP_LOOK "..............:Mirar la habitación.\n"
#define HELP_NORTH "..............:Desplazarse a la habitación del norte.\n"
#define HELP_WEST "..............:Desplazarse a la habitación del oeste.\n"
#define HELP_EXITS "............:Ver las salidar de la habitación.\n"
#define HELP_DROP " <Objeto>.....:Tirar un objeto al suelo.\n"
#define HELP_GET_FROM_BAG " <Objeto>.....:Pasar un objeto de la bolsa al inventario.\n"
#define HELP_SOUTH "................:Desplazarse a la habitación del sur.\n"


//macro
#define Put_in_bag(x) "Guardas %s en la bolsa.\n\n", x
#define Not_In_bag(x) "En tu bolsa no hay %s.\n\n", x
#define Inventory_void(x) "No tienes %s en tu inventario.\n\n", x
#define Pick(x) "Pones %s en tu inventario.\n\n", x
#define Not_found(x) "Lo siento no encuentro %s.\n\n", x
#define Drop_Item(x) "Tiras %s al suelo.\n\n", x
#define Show_Item(x) " -%s.\n\n", x
#define Read_from_Room(x) "\n%s\n", x
#define colortext(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x); //necesita #include <windows.h>