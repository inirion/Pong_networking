#include "Ball.h"
#include <iostream>



void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ball);
}

void Ball::update()
{
	std::cout << position.x << std::endl;
	move(movingCoords, speed);
	std::cout << position.x << std::endl;
	ball.setPosition(position);
}

Ball::Ball(sf::RenderWindow& window) :rw(window)
{
	ball.setRadius(5.5f);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(sf::Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setPosition(sf::Vector2f(10, 10));
	movingCoords = sf::Vector2f(-1, 0);
	speed = 5.0f;
}


Ball::~Ball()
{
}
