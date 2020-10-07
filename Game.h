#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include "Player.h"
#include "Coin.h"
#include "Asteroid.h"

/*
* Game Manager Class
*/

class Game
{
public:									//--Public--
	Game();
	virtual ~Game();

	const bool getWindowStat() const;

	void updateEvent();

	void spawnAsteroid();
	void updateAsteroids();
	void renderAsteroids();

	void spawnCoins();

	void updateColission();
	void update();
	void render();
	void updateGUI();
	void renderGUI(sf::RenderTarget* target);

private:								//--Private--

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Vector2i mousePosWindow;

	bool endGame;						//Default Var.

	int points;

	float asteroidSpeed;
	float asteroidSpawnTimerMax;		//Asteroid Var.
	float asteroidSpawnTimer;
	int maxAsteroids;

	float coinSpawnTimerMax;			//Coin Var.
	float coinSpawnTimer;
	int maxCoins;

	void initVariables();
	void initWindow();
	void initAsteroids(); //-this
	void initFont();
	void initText();
	void exitGame();

	//Game Objects
	Player* player;

	std::vector<sf::RectangleShape> asteroids;
	std::vector<Coin*> coins;

	sf::Font pointFont;
	sf::Text pointText;
	sf::RectangleShape asteroid;
};

