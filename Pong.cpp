#include "Pong.h"
#include "Config.h"

void Pong::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	player1->draw(target, states);
	player2->draw(target, states);
	ball->draw(target, states);
}

void Pong::update()
{
	sf::Packet packet;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (Config::isServer) {
			packet << *player1 << 1;
			client.Send(packet);
		}
		else {
			packet << *player2 << 1;
			client.Send(packet);
		}
	}

	
	
	
	if (Config::isServer) {
		player1->update();
		ball->update();
		Collision();
		packet << *ball << 2;
		client.Send(packet);
	}
	else {

		player2->update();
	}

	switch (client.Recive()) {
	case sf::Socket::Done: {
		if (Config::isServer) {
			player2->readFromPacket(client.getPacket());
			int x;
			client.getPacket() >> x >> x >> x;
			if(x == 1)
			player2->movePaddle();
		}
		else {
			player1->readFromPacket(client.getPacket());
			int x;
			client.getPacket() >> x >> x >> x;
			if (x == 1)
			player1->movePaddle();
			switch (client.Recive()) {
			case sf::Socket::Done: {
				ball->readFromPacket(client.getPacket());
				int x;
				client.getPacket() >> x >> x >> x;
				if (x == 2)
				ball->moveBall();
			}break;
			}
			
		}
	}
		break;
	};
	
	
}

void Pong::Collision()
{
	if (ball->getBallRect().intersects(player1->getPaddleRect())) {

		float angle = 0.f;
		if (ball->getBall().getPosition().x <= player1->getPaddle().getPosition().x + ball->getSpeed()) {
			if (ball->getBall().getPosition().y <= player1->getPaddle().getPosition().y
				&& ball->getBall().getPosition().y >= player1->getPaddle().getPosition().y - player1->getPaddle().getSize().y) {
				std::cout << "top interact : " << std::endl;
				float lenghtOfUpperPaddle = player1->getPaddle().getPosition().y - ball->getBall().getPosition().y;
				angle = lenghtOfUpperPaddle / 35.f*-1;
			}
			else if (ball->getBall().getPosition().y >= player1->getPaddle().getPosition().y
				&& ball->getBall().getPosition().y <= player1->getPaddle().getPosition().y + player1->getPaddle().getSize().y) {
				std::cout << "bottom interact : " << std::endl;
				float lenghtOfUpperPaddle = player1->getPaddle().getPosition().y - ball->getBall().getPosition().y;
				angle = lenghtOfUpperPaddle / 35.f*-1;
			}
			ball->setMovingCoords(sf::Vector2f(1, angle));
		}

	}
	if (ball->getBallRect().intersects(player2->getPaddleRect())) {

		float angle = 0.f;
		if (ball->getBall().getPosition().x >= player1->getPaddle().getPosition().x - ball->getSpeed()) {
			if (ball->getBall().getPosition().y <= player2->getPaddle().getPosition().y
				&& ball->getBall().getPosition().y >= player2->getPaddle().getPosition().y - player2->getPaddle().getSize().y) {
				float lenghtOfUpperPaddle = player2->getPaddle().getPosition().y - ball->getBall().getPosition().y;
				angle = lenghtOfUpperPaddle / 35.f *-1;
			}
			else if (ball->getBall().getPosition().y >= player2->getPaddle().getPosition().y
				&& ball->getBall().getPosition().y <= player2->getPaddle().getPosition().y + player2->getPaddle().getSize().y) {
				float lenghtOfUpperPaddle = player2->getPaddle().getPosition().y - ball->getBall().getPosition().y;
				angle = lenghtOfUpperPaddle / 35.f *-1;
			}
			ball->setMovingCoords(sf::Vector2f(-1, angle));
		}
	}
	if (ball->getBall().getPosition().y <= 0) {
		ball->setMovingCoords(sf::Vector2f(ball->getMovingCoords().x, ball->getMovingCoords().y*-1.f));
	}
	if (ball->getBall().getPosition().y >= rw.getSize().y) {
		ball->setMovingCoords(sf::Vector2f(ball->getMovingCoords().x, ball->getMovingCoords().y*-1.f));
	}
	if (ball->getBall().getPosition().x >= rw.getSize().x) {
		ball->reset(sf::Vector2f(rw.getSize().x / 2, rw.getSize().y / 2));
	}
	if (ball->getBall().getPosition().x <= 0) {
		ball->reset(sf::Vector2f(rw.getSize().x / 2, rw.getSize().y / 2));
	}
}

Pong::Pong(sf::RenderWindow & window, Client &c) : rw(window), client(c)
{
	player1 = new Paddle(window,false);
	player2 = new Paddle(window,true);
	ball = new Ball(window);
	lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
}


Pong::~Pong()
{
}