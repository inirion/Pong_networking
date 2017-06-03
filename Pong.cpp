#include "Pong.h"
#include "Config.h"

void Pong::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	player1->draw(target, states);
	player2->draw(target, states);
	ball->draw(target, states);
	target.draw(score);
}

void Pong::update(sf::Event e, Client &c, Server &s)
{	
	if (Config::isServer) {
		player1->update();
		ball->update();
		Collision(s);
	}
	else {
		player2->update();
	}
	if (Config::clock.getElapsedTime().asMilliseconds() - lastFrameTime >= 10) {
		
		lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
	}
	SendData(c, s);
	RecvData(c, s);
	
}

void Pong::SendScore(Server & s)
{
	if (Config::isServer) {
		sf::Packet p;
		p << packetStates::SCORE << enemyScore << playerScore;
		s.Send(p);
	}
}

void Pong::SendData(Client &c, Server &s)
{
	if (Config::isServer) {
		sf::Packet p1;
		p1 << packetStates::PLAYING << player1->getPosition().x << player1->getPosition().y << ball->getPosition().x << ball->getPosition().y;
		if (s.Send(p1)) std::cout << " SerwerSend Success" << std::endl;
		else std::cout << " SerwerSend error" << std::endl;
	}
	else {
		sf::Packet p2;
		p2 << packetStates::PLAYING << player2->getPosition().x << player2->getPosition().y;
		if (c.Send(p2)) std::cout << " KlientSend Success" << std::endl;
		else std::cout << " KlientSend error" << std::endl;
	}
}

void Pong::RecvData(Client &c, Server &s)
{
	float x1, x2, y1, y2;
	int type;
	unsigned short scorePointsTemp;
	sf::Packet p;
	if (Config::isServer) {
		if (s.Recive(p)) {
			if (p >> type) {
				std::cout << type << std::endl;
				switch (type)
				{
				case packetStates::PLAYING: {
					if (p >> x1 >> y1) {
						player2->setPosition(sf::Vector2f(x1, y1));
						player2->movePaddle();
					}
				}break;
				default:
					break;
				}
			}
			
		}
	}
	else {
		if (c.Recive(p)) {
			if (p >> type) {
				
				switch (type)
				{
				case packetStates::PLAYING: {
					if (p >> x1 >> y1 >> x2 >> y2) {
						std::cout << type << std::endl;
						player1->setPosition(sf::Vector2f(x1, y1));
						player1->movePaddle();
						ball->setPosition(sf::Vector2f(x2, y2));
						ball->moveBall();
					}
				}break;
				case packetStates::SCORE: {
					if (p >> playerScore >> enemyScore) {
						std::string scoreText = std::to_string(playerScore) + " : " + std::to_string(enemyScore);
						score.setString(scoreText);
					}
				}
				default:
					break;
				}
			}
			
		}
	}
}

void Pong::Collision(Server &s)
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
		playerScore++;
		std::string scoreText = std::to_string(playerScore) + " : " + std::to_string(enemyScore);
		score.setString(scoreText);
		SendScore(s);
		ball->reset(sf::Vector2f(rw.getSize().x / 2, rw.getSize().y / 2));
	}
	if (ball->getBall().getPosition().x <= 0) {
		enemyScore++;
		std::string scoreText = std::to_string(playerScore) + " : " + std::to_string(enemyScore);
		score.setString(scoreText);
		SendScore(s);
		ball->reset(sf::Vector2f(rw.getSize().x / 2, rw.getSize().y / 2));
	}
}

Pong::Pong(sf::RenderWindow & window) : rw(window)
{
	player1 = new Paddle(window,false);
	player2 = new Paddle(window,true);
	playerScore = 0;
	enemyScore = 0;
	ball = new Ball(window);
	font.loadFromFile("DroidSansMono.ttf");
	score.setFont(font);
	score.setPosition(sf::Vector2f(rw.getSize().x/2, rw.getSize().y/10));
	score.setString("0 : 0");
	score.setCharacterSize(40);
	score.setFillColor(sf::Color::Blue);
	lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
}


Pong::~Pong()
{
}