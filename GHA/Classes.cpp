#include "Classes.h"

//----------------
//GameObject------
//----------------

GameObject::GameObject(int x = (int)SCREENW / 2, int y = (int)SCREENH / 2) : corX(x), corY(y) {/**/ }

int GameObject::getX()const
{
	return corX;
}

int GameObject::getY()const
{
	return corY;
}

//----------------
//HurtsPlayer-----
//----------------

//----------------
//Block-----------
//----------------

Block::Block() : GameObject(0, 0) {}

Block::Block(int x, int y, std::string minta = "") : GameObject(x, y)
{
	if (minta == "")
		std::cout << "Error!" << std::endl;

	if (!texture.loadFromFile(minta))
	{
		std::cerr << "Hiba a mintázat betöltésénél" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(corX, corY);
	sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
	sprite.setScale(BLOCKSIZEW / 200.0, BLOCKSIZEH / 200.0);
}

void Block::update(sf::RenderWindow * window)
{
	window->draw(sprite);
}

sf::Sprite Block::getSprite() const
{
	return sprite;
}

Block& Block::operator=(const Block & oth)
{
	if (this == &oth)
		return *this;

	corX = oth.corX;
	corY = oth.corY;

	texture.operator=(oth.texture);

	sprite.setTexture(texture);
	sprite.setPosition(corX, corY);
	sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
	sprite.setScale(BLOCKSIZEW / 200.0, BLOCKSIZEH / 200.0);

	return *this;
}

//----------------
//Palya-----------
//----------------

Palya::Palya(std::ifstream & terkep)
{
	int tmp, i = 0;
	std::vector<int> poz;

	darab = 0;

	//mintaUt = "wall.png";

	while (!terkep.eof())
	{
		terkep >> tmp;

		if (tmp == 1)
		{
			darab++;
			poz.push_back(i);
		}

		terkep >> std::ws;
		i++;
	}
	delete[] Blocks;
	Blocks = new Block[darab];
	for (int i = 0; i < darab; i++)
	{
		Blocks[i].operator= (Block((poz.back() % BLOCKNUM) * BLOCKSIZEW, (poz.back() / BLOCKNUM) * BLOCKSIZEH, mintaUt));
		poz.pop_back();
	}
}

void Palya::updatePalya(sf::RenderWindow * window)
{
	for (int i = 0; i < darab; i++)
	{
		Blocks[i].update(window);
	}
}

Palya::~Palya()
{
	delete[] Blocks;
}

//----------------
//Moving----------
//----------------

Moving::Moving(int corX = (int)SCREENW / 2, int corY = (int)SCREENH / 2, double vX = 1, double vY = 1) : GameObject(corX, corY), velocityX(vX), velocityY(vY)
{}

void Moving::setVelocityX(double x)
{
	velocityX = x;
}

void Moving::setVelocityY(double y)
{
	velocityY = y;
}

void Moving::move(/*T&*/ Palya * oth, sf::Sprite sp)
{
	bool volt = false;

	sf::FloatRect rTmp;

	for (int i = 0; i < oth->getDatab(); i++) {
		if (oth->operator[](i).getSprite().getGlobalBounds().intersects(sp.getGlobalBounds()))
		{
			rTmp = oth->operator[](i).getSprite().getGlobalBounds();
			if (rTmp.top <= corY + sp.getGlobalBounds().height &&
				rTmp.top >= corY + sp.getGlobalBounds().height - (int)(gravity * 15))
			{
				volt = true;
				setVelocityY(gravity);
				if ((corX >= rTmp.left && corX <= rTmp.left + BLOCKSIZEW) || (corX + sp.getGlobalBounds().width >= rTmp.left && corX + sp.getGlobalBounds().width <= rTmp.left + BLOCKSIZEW))
					if (corX + (int)(BLOCKNUM * velocityX) < SCREENW && corX + (int)(BLOCKNUM * velocityX) > 0)
						corX += (int)(BLOCKNUM * velocityX);
			}

			else if (rTmp.top + 5 < corY + sp.getGlobalBounds().height && rTmp.top + rTmp.height - (int)(gravity * 15) > corY + sp.getGlobalBounds().height)
			{
				volt = true;
				setVelocityY(gravity);
				if (rTmp.left < corX)
					corX += abs(velocityX) * BLOCKNUM;
				else corX -= abs(velocityX) * BLOCKNUM;
			}

			else if (rTmp.top + rTmp.height <= corY + sp.getGlobalBounds().height &&
				rTmp.top + rTmp.height >= corY + sp.getGlobalBounds().height - (int)(gravity * 15))
			{
				volt = true;
				setVelocityY(gravity);
				if (rTmp.left < corX)
					corX += abs(velocityX) * BLOCKNUM + 10;
				else corX -= abs(velocityX) * BLOCKNUM + 10;
			}
		}
	}
	if (!volt)
	{
		if (corX + (int)(BLOCKNUM * velocityX) < SCREENW && corX + (int)(BLOCKNUM * velocityX) > 0)
			corX += (int)(BLOCKNUM * velocityX);

		if (corY + (int)BLOCKNUM * velocityY < SCREENH)
			corY += (int)BLOCKNUM * velocityY;
	}
	while (corX + BLOCKSIZEW > SCREENW)
		corX--;
}

//----------------
//Player----------
//----------------

Player::Player(Palya * palya, int corX = (int)SCREENW / 2, int corY = (int)SCREENH / 2, double vX = 1, double vY = 1, int id = 0) :Moving(corX, corY, vX, vY)
{
	if (id < 0 || id>1);

	this->palya = palya;
	this->id = id;

	std::string minta;

	if (id == 0)
		minta = "FriendDino_1.png";
	else
		minta = "minta2";

	if (!texture.loadFromFile(minta))
	{
		std::cerr << "Hiba a mintázat betöltésénél" << std::endl;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setPosition(corX, corY);
	sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
	sprite.setScale(BLOCKSIZEW / (double)texture.getSize().x * 0.9, BLOCKSIZEW / (double)texture.getSize().x * 0.9);
}

void Player::jump()
{
	bool volt = false;

	corY -= BLOCKSIZEH * 1.5;
	sprite.setPosition(corX, corY);

	for (int i = 0; i < palya->getDatab(); i++)
		if (palya->operator[](i).getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()))
			volt = true;

	if (volt)
	{
		corY += BLOCKSIZEH * 0.9;
		sprite.setPosition(corX, corY);
		setVelocityY(1.1);
	}
}

void Player::update(sf::RenderWindow * window)
{
	move(palya, sprite);
	sprite.setPosition(corX, corY);
	window->draw(sprite);
}

//----------------
//Status----------
//----------------