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
extern std::string* nevek;

const std::string fileUt = "Test.txt";

//std::vector<coordinate> Fixcoords;

//sf::RenderWindow window(sf::VideoMode(800, 600), "SupeDino");
// szia :)
// mizu? sok sikert a házihoz, ha ezt épp hajnali egy után olvasod akkor menj aludni!!!!!

#endif // !_GLOBALS_H_