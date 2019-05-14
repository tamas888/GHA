#pragma once
#include "includes.h"

class GameObject
{
protected:
	int corX, corY;
	//char* name;
	//bild;
public:
	GameObject();
	GameObject(int x, int y);

	int getX()const;
	int getY()const;

	//~GameObject();
	virtual void update(sf::RenderWindow* window) = 0;
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
	Palya() { Blocks = NULL; }
	Palya(std::ifstream& terkep);
	Palya(const Palya* oth) { Blocks = NULL; if (oth != NULL) * this = oth; }
	int getDatab()const { return darab; }
	void updatePalya(sf::RenderWindow * window);

	Block operator[] (int a)const { return Blocks[a]; }
	~Palya();
};

class Moving : public virtual GameObject
{
	double velocityX, velocityY;
protected:
	void move(Palya* oth, sf::Sprite sp, bool ellen);
public:
	Moving() :GameObject(0, 0) {}
	Moving(int corX, int corY, double vX, double vY);
	void setVelocityX(double vX);
	void setVelocityY(double vY);
	double getVX() const { return velocityX; }
	double getVY() const { return velocityY; }
	virtual void jump() { return; };
	virtual void update(sf::RenderWindow* window) = 0;
};

class Player : public Moving
{
	sf::Texture texture;
	sf::Sprite sprite;
	Palya* palya;
	//name
	int id;
	int health;
public:
	void jump() override;
	Player();
	Player(Palya* palya, int corX, int corY, double vx, double vy, int id, int health);
	Player(const Player& oth);

	void update(sf::RenderWindow* window)override;
	sf::Sprite getSprite()const { return sprite; }
	void setHealth(const int damage) { health += damage; }
	~Player();
};

class Status : public virtual GameObject
{
protected:
	int damage;
	sf::Texture texture;
	sf::Sprite sprite;
	bool letezik;
	Player* players;
public:
	Status() : GameObject(0, 0) { players = NULL; bool letezik = false; };
	Status(Player* players, std::string minta, int damage, int x, int y);
	Status(const Status& oth) :GameObject(oth.corX, oth.corY) { players = NULL; *this = oth; }

	Player* getPlayers() const { return players; }
	void utkozik();
	void update(sf::RenderWindow* window) override;
	~Status();
};

class Enemy : public Moving, public Status
{
	int vXhatar, kezY;
	Palya* palya;
	bool csokken;
public:
	Enemy() :Moving(NULL, NULL, NULL, NULL), Status(), GameObject(NULL, NULL) { palya = NULL; }
	Enemy(Palya* palya, Player* players, std::string minta, int damage, double vX, double vY, int x, int y);
	Enemy(const Enemy& oth) :GameObject(NULL, NULL), Moving(NULL, NULL, NULL, NULL), Status(NULL, NULL, NULL, NULL, NULL) { palya = NULL; *this = oth; }

	void jump()override { return; }
	void moveLimit();
	void update(sf::RenderWindow* window) override;
};