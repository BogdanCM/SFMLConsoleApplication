#include "Coin.h"

Coin::Coin(const sf::RenderWindow& window)
{
	this->initShape(window);
}

Coin::~Coin()
{

}

const sf::CircleShape Coin::getShape() const
{
	return this->circleShape;
}

void Coin::update()
{

}

void Coin::renderCoin(sf::RenderTarget & target)
{
	target.draw(this->circleShape);
}

void Coin::initShape(const sf::RenderWindow & window)
{
	this->circleShape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->circleShape.setFillColor(color);
	this->circleShape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->circleShape.getGlobalBounds().width), 
		static_cast<float>(rand() % window.getSize().y - this->circleShape.getGlobalBounds().height)));

}
