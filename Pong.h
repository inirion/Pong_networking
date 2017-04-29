#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "Client.h"


class Pong : public sf::Drawable
{
private :
	Paddle *player1;
	Paddle *player2;
	Ball *ball;
	Client &client;
	sf::RenderWindow &rw;
	sf::Int32 lastFrameTime;
public:
	void Collision();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
	Pong(sf::RenderWindow& window, Client &c);
	~Pong();
};

