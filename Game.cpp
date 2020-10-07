#include "Game.h"

void Game::initVariables() //Private Func.
{
	this->window = nullptr;
	this->endGame = false;

	this->points = 0;
	this->player = new Player();

	this->asteroidSpeed = 6.f;
	this->asteroidSpawnTimerMax = 30.f;
	this->asteroidSpawnTimer = this->asteroidSpawnTimerMax;
	this->maxAsteroids = 500;

	this->coinSpawnTimerMax = 10.f;
	this->coinSpawnTimer = this->coinSpawnTimerMax;
	this->maxCoins = 10;
}

void Game::initWindow() //Private Func.
{
	this->videoMode.height = 800;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Asteroids.io", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initAsteroids()
{
	this->asteroid.setPosition(10.f, 10.f);
	this->asteroid.setSize(sf::Vector2f(100.f, 100.f));
	this->asteroid.setScale(sf::Vector2f(0.7f, 0.7f));
	this->asteroid.setOutlineColor(sf::Color::White);
	this->asteroid.setOutlineThickness(1.f);
}

void Game::initFont()
{
	if (!this->pointFont.loadFromFile("Fonts/Minecraft.ttf"))
	{
		std::cout << "Could not fetch Font!" << "\n";
	}
}

void Game::initText()
{
	this->pointText.setFont(this->pointFont);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setCharacterSize(32);
}

void Game::exitGame()
{
	if(this->endGame == true)
	{
		this->window->close();
	}
}

Game::Game()	//Constructor
{
	this->initVariables();
	this->initWindow();
	this->initAsteroids();
	this->initFont();
	this->initText();
}

Game::~Game()	//Destructor
{
	delete this->window;
	delete this->player;

	for (auto* i : this->coins)
	{
		delete i;
	}
}

const bool Game::getWindowStat() const
{
	return this->window->isOpen();
}

void Game::spawnAsteroid()
{
	this->asteroid.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->asteroid.getSize().x)),0.f);

	this->asteroid.setFillColor(sf::Color::Red);
	this->asteroids.push_back(this->asteroid);
}

void Game::updateEvent()	//Event Initializer
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateAsteroids()
{
	if (this->asteroids.size() < this->maxAsteroids) 
	{
		if (this->asteroidSpawnTimer >= this->asteroidSpawnTimerMax) 
		{
			this->spawnAsteroid();
			this->asteroidSpawnTimer = 0.f;
		}
		else
			this->asteroidSpawnTimer += 1.f;
	}

	for(auto &e : this->asteroids)
	{
		e.move(0.f, asteroidSpeed);
	}
}

void Game::updateColission()	//Collission Manager
{
	for (size_t i = 0; i < this->coins.size(); i++)
	{
		if (this->player->getShape().getGlobalBounds().intersects(this->coins[i]->getShape().getGlobalBounds()))
		{
			this->coins.erase(this->coins.begin() + i);
			this->points++;
		}
	}

	for (size_t i = 0; i < this->asteroids.size(); i++)
	{
		if (this->player->getShape().getGlobalBounds().intersects(this->asteroids[i].getGlobalBounds()))
		{
			this->endGame = true;
		}
	}
}

void Game::update()			//Update Func.
{
	this->updateEvent();
	this->spawnCoins();
	this->updateAsteroids();
	this->updateColission();
	this->player->update(this->window);
	this->updateGUI();
	this->exitGame();
}

void Game::renderAsteroids()
{
	for (auto& e : this->asteroids)
	{
		this->window->draw(e);
	}
}

void Game::spawnCoins()
{

	if (this->coinSpawnTimer< this->coinSpawnTimerMax)
		this->coinSpawnTimer += 1.f;

	else
	{
		if (this->coins.size() < this->maxCoins)
		{
			this->coins.push_back(new Coin(*this->window));
			this->coinSpawnTimer = 0.f;
		}
	}
}

void Game::render() //Render Game Window
{
	this->window->clear();
	this->renderAsteroids();
	this->player->render(this->window);

	for(auto i : this->coins)
	{
		i->renderCoin(*this->window);
	}

	this->renderGUI(this->window);

	this->window->display();
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
}

void Game::renderGUI(sf::RenderTarget* target)
{
	target->draw(this->pointText);
}
