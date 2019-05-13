#pragma once
#include "includes.h"

class GameObject
{
protected:
	int corX, corY;
	//char* name;
	//bild;
public:
	GameObject(int x, int y);

	int getX()const;
	int getY()const;

	//~GameObject();
	virtual void update(sf::RenderWindow* window) = 0;
};

class HurtsPlayer : virtual public GameObject
{
	//void update();
};

class Block : public GameObject
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Block();
	Block(int x, int y, std::string minta);
	//Block(Block& oth);
	void update(sf::RenderWindow* window);
	sf::Sprite getSprite()const;
	Block& operator=(const Block& oth);
};

class Palya
{
	Block* Blocks;
	int darab;
	std::string mintaUt = "wall.png";
public:
	Palya(std::ifstream& terkep);
	int getDatab()const { return darab; }
	void updatePalya(sf::RenderWindow* window);

	Block operator[] (int a)const { return Blocks[a]; }
	~Palya();
};

class Moving : public GameObject
{
	double velocityX, velocityY;
protected:
	void move(Palya* oth, sf::Sprite sp);
public:
	Moving(int corX, int corY, double vX, double vY);
	void setVelocityX(double vX);
	void setVelocityY(double vY);
	virtual void jump() = 0;
	virtual void update(sf::RenderWindow* window) = 0;
};

class Player : public Moving
{
	sf::Texture texture;
	sf::Sprite sprite;
	Palya* palya;
	//name
	int id;
public:
	void jump() override;
	Player(Palya* palya, int corX, int corY, double vx, double vy, int id);
	void update(sf::RenderWindow* window)override;
};

class Status : public GameObject
{
	int dam
};