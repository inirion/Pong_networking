#include "Pong.h"
#include "Config.h"

void Pong::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	player1->draw(target, states);
	player2->draw(target, states);
	ball->draw(target, states);
}

void Pong::update(sf::Event e, Client &c, Server &s)
{	
	if (Config::isServer) {
		player1->update();
		ball->update();
		Collision();
	}
	else {
		player2->update();
	}
	if (Config::clock.getElapsedTime().asMilliseconds() - lastFrameTime >= 1000) {
		SendData(c, s);
		lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
	}
	
	RecvData(c, s);
	
}

void Pong::SendData(Client &c, Server &s)
{
	if (Config::isServer) {
		sf::Packet p1;
		int value = 1;
		p1 << value;
		if (s.Send(p1)) std::cout << " SerwerSend Success" << std::endl;
		else std::cout << " SerwerSend error" << std::endl;
	}
	else {
		sf::Packet p2;
		int value = 1;
		p2 << value;
		if (c.Send(p2)) std::cout << " KlientSend Success" << std::endl;
		else std::cout << " KlientSend error" << std::endl;
		
	}
}

void Pong::RecvData(Client &c, Server &s)
{
	if (Config::isServer) {
		if (s.Recive()) {
			int a;
			s.getPacket() >> a;
			std::cout << a << std::endl;
		}
	}
	else {
		if (c.Recive()) {
			int b;
			c.getPacket() >> b;
			std::cout << b << std::endl;
		}
	}
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

Pong::Pong(sf::RenderWindow & window) : rw(window)
{
	player1 = new Paddle(window,false);
	player2 = new Paddle(window,true);
	ball = new Ball(window);
	lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
}


Pong::~Pong()
{
}