#include "includes.h"

sf::Event event;
sf::Color background;
sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "SupeDino");
int playerNum = 0;

using namespace sf;

int main()
{
	window.setKeyRepeatEnabled(true);

	std::cout << "Hany jatekos van?" << std::endl;
	//std::cin >> playerNum;
	playerNum = 1;
	setParameter();

	//Block wall(200, 200, "wall.png");

	std::ifstream test("Test.txt");

	Palya palya1(test);
	Player dino1(&palya1, 50, 50, 0, gravity, 0, 100);
	Status juatlom(&dino1, "jutalom.png", 15, 200, 300);

	while (window.isOpen())
	{
		eventCheck(window, dino1);
		//dino1.setVelocityX(-0.1);

		window.clear(background);

		palya1.updatePalya(&window);

		dino1.update(&window);

		juatlom.update(&window);

		window.display();
	}

	return 0;
}