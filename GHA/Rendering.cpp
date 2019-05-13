#include"includes.h"
#include "Classes.h"

void setParameter()
{
	background = sf::Color::Color(0, 229, 225);
}

void eventCheck(sf::RenderWindow& window, Player& player)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::Right:
				player.setVelocityX(0.5);
				break;
			case sf::Keyboard::Left:
				player.setVelocityX(-0.5);
				break;
			}

			break;

		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				player.jump();
				break;
			default:
				player.setVelocityX(0);
				break;
			}
		default:
			break;
		}
	}
}