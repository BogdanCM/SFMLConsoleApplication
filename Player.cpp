#include "Player.h"

void Player::initVariables()
{
	this->playerSpeed = 5.f;
	this->hpMax = 8;
	this->hp = hpMax;
}

Player::Player(float x, float y)
{
	this->playerShape.setPosition(x, y);
	this->initVariables();
	this->initShapes();
}

Player::~Player()
{

}

const sf::RectangleShape& Player::getShape() const
{
	return this->playerShape;
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateWindowBoundsColission(target);
	this->updateInput();
}

void Player::updateInput()
{
	/*Input managing & Player Movement*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->playerShape.move(-this->playerSpeed, 0.f);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->playerShape.move(this->playerSpeed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->playerShape.move(0.f, -this->playerSpeed);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->playerShape.move(0.f, this->playerSpeed);
	}
}

void Player::updateWindowBoundsColission(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->playerShape.getGlobalBounds();
	if (playerBounds.left <= 0.f)
		this->playerShape.setPosition(0.f, playerBounds.top);

	if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->playerShape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);

	if (playerBounds.top <= 0.f)
		this->playerShape.setPosition(playerBounds.left, 0.f);

	if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->playerShape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->playerShape);
}

void Player::initShapes()
{
	this->playerShape.setFillColor(sf::Color::White);
	this->playerShape.setSize(sf::Vector2f(60.f, 60.f));
	this->playerShape.setPosition(260.f, 700.f);
}
