#include "includes.h"

sf::Event event;
sf::Color background;
sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "SupeDino");

int playerNum = 0;
int jutalomNum = 0;
int ellensegNum = 0;

Palya palya1;
Player* jatekosok;
Status* jutalmak;
Enemy* ellensegek;
std::string* nevek;

using namespace sf;

void init();

int main()
{
	window.setKeyRepeatEnabled(true);

	init();

	while (window.isOpen())
	{
		window.clear(background);

		palya1.updatePalya(&window);

		for (int i = 0; i < playerNum; i++)
			jatekosok[i].update(&window);

		for (int i = 0; i < jutalomNum; i++)
			jutalmak[i].update(&window);

		for (int i = 0; i < ellensegNum; i++)
			ellensegek[i].update(&window);

		window.display();
	}

	return 0;
}

void init() {
	background = sf::Color::Color(0, 229, 225);

	std::cout << "Udvozlom!" << std::endl << "Eloszor szuksegem lesz par informaciora Ontol es utana kezdhetjuk is a jatekot. :)" << std::endl;
	std::cout << "Hany jatekos van? (Maximum ketto jatekos lehet)" << std::endl;

	std::string tmp;

	std::cin >> tmp;
	while (tmp != "1" && tmp != "2")
	{
		std::cout << "A megadott felhasznaloszam nem helyes!" << std::endl << "Kerem adjon meg helyes szamot (1 vagy 2 jatekos)!" << std::endl;
		std::cin >> tmp;
	}

	playerNum = tmp[0] - '0';
	nevek = new std::string[playerNum];

	for (int i = 0; i < playerNum; i++)
	{
		std::cout << "Kerem a(z) " << i + 1 << ". jatekos nevet:";
		std::cin >> nevek[i];
	}

	std::ifstream palyaFile(fileUt);
	palya1 = Palya(palyaFile);

	int tmpi, i = 0;
	std::vector<int> poz[3];

	enum { jat, jut, ell };

	while (!palyaFile.eof())
	{
		palyaFile >> tmpi;

		if (tmpi == jat + 2)
		{
			poz[jat].push_back(i);
		}
		else if (tmpi == jut + 2)
		{
			poz[jut].push_back(i);
		}
		else if (tmpi == ell + 2)
		{
			poz[ell].push_back(i);
		}
		palyaFile >> std::ws;
		i++;
	}

	if (poz[jat].size() == 1 || poz[jat].size() == 2) {
		playerNum = poz[jat].size();
	}
	else
	{
		playerNum = 1;
	}

	jatekosok = new Player[playerNum];

	for (int i = 0; i < playerNum; i++)
	{
		jatekosok[i] = Player(&palya1, poz[jat].back() / BLOCKNUM, poz[jat].back() % BLOCKNUM, 0, gravity, i, 100);
		poz[jat].pop_back();
	}

	jutalomNum = poz[jut].size();
	jutalmak = new Status[jutalomNum];

	for (int i = 0; i < jutalomNum; i++)
	{
		jutalmak[i] = Status(jatekosok, "jutalom.png", rand() % 31 + 30, poz[jut].back() / BLOCKNUM, poz[jut].back() % BLOCKNUM);
		poz[jut].pop_back();
	}

	ellensegNum = poz[ell].size();
	ellensegek = new Enemy[ellensegNum];
	for (int i = 0; i < ellensegNum; i++)
	{
		ellensegek[i] = Enemy(&palya1, jatekosok, "ellenseg.png", rand() % 20 + 10, rand() % 2, 0, poz[ell].back() / BLOCKNUM, poz[ell].back() % BLOCKNUM);
		poz[ell].pop_back();
	}
}