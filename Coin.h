#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Coin
{

public:
	Coin(const sf::RenderWindow& window);
	virtual ~Coin();

	const sf::CircleShape getShape() const;

	void update();
	void renderCoin(sf::RenderTarget& target);

private:
	sf::CircleShape circleShape;

	void initShape(const sf::RenderWindow& window);
};

