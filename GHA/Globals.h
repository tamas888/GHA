#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Main.hpp"
#include <vector>

#define SCREENW 900
#define SCREENH 900
#define BLOCKNUM 10

const int BLOCKSIZEW = SCREENW / BLOCKNUM;
const int BLOCKSIZEH = SCREENH / BLOCKNUM;
const double gravity = 0.6;

extern sf::Event event;
extern sf::Color background;
extern sf::RenderWindow window;

extern int playerNum;

struct coordinate
{
	int kezX, kezY, vegX, vegY;
};

//std::vector<coordinate> Fixcoords;

//sf::RenderWindow window(sf::VideoMode(800, 600), "SupeDino");
// szia :)
// mizu? sok sikert a h�zihoz, ha ezt �pp hajnali egy ut�n olvasod akkor menj aludni!!!!!

#endif // !_GLOBALS_H_