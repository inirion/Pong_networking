#include "Paddle.h"
#include <iostream>


void Paddle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(paddle);
}

void Paddle::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y - paddle.getSize().y / 2 > 0) {
		position.y -= 5;
		movePaddle();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y + paddle.getSize().y / 2 < rw.getSize().y) {
		position.y += 5;
		movePaddle();
	}
}

void Paddle::movePaddle() {
	paddle.setPosition(position);
}
void Paddle::setPosition(sf::Vector2f pos)
{
	this->position = pos;
}

Paddle::Paddle(sf::RenderWindow& window,bool ai) :rw(window)
{
	if (!ai) {
		paddle.setSize(sf::Vector2f(20.f, 120.f));
		paddle.setPosition(sf::Vector2f((float)(paddle.getSize().x * 2), (float)(rw.getSize().y / 2)));
		paddle.setOrigin(sf::Vector2f(paddle.getSize().x / 2, paddle.getSize().y / 2));
		paddle.setFillColor(sf::Color::Red);
		position = paddle.getPosition();
	}
	else {
		paddle.setSize(sf::Vector2f(20.f, 120.f));
		paddle.setPosition(sf::Vector2f((float)(rw.getSize().x - paddle.getSize().x * 2), (float)(rw.getSize().y / 2)));
		paddle.setOrigin(sf::Vector2f(paddle.getSize().x / 2, paddle.getSize().y / 2));
		paddle.setFillColor(sf::Color::Blue);
		position = paddle.getPosition();
	}

}



Paddle::~Paddle()
{
}
