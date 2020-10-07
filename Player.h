#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Player
{
public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	const sf::RectangleShape& getShape() const;

	void updateInput();
	void updateWindowBoundsColission(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

private:
	sf::RectangleShape playerShape;

	float playerSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initShapes();
};