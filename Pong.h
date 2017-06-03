#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "Client.h"
#include "Server.h"

class Pong : public sf::Drawable
{
private :
	enum packetStates {
		PLAYING,
		SCORE,
	};
	Paddle *player1;
	Paddle *player2;
	Ball *ball;
	sf::RenderWindow &rw;
	sf::Int32 lastFrameTime;
	sf::Text score;
	sf::Font font;
	unsigned short playerScore;
	unsigned short enemyScore;
public:
	void Collision(Server &s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Event e, Client &c, Server &s);
	void SendScore(Server &s);
	void SendData(Client &c, Server &s);
	void RecvData(Client &c, Server &s);
	Pong(sf::RenderWindow& window);
	~Pong();
};

