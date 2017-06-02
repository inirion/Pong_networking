#include "Ball.h"
#include <iostream>



void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ball);
}

void Ball::update()
{
	move(movingCoords, speed);
	ball.setPosition(position);
}

Ball::Ball(sf::RenderWindow& window) :rw(window)
{
	ball.setRadius(5.5f);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(sf::Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setPosition(sf::Vector2f(rw.getSize().x/2, rw.getSize().y / 2));
	movingCoords = sf::Vector2f(1, 0);
	speed = 5.0f;
}


Ball::~Ball()
{
}
