#include "Lobby.h"

void Lobby::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto button : buttons) {
		target.draw(button);
	}
	for (auto text : texts) {
		target.draw(text);
	}
}

void Lobby::update(std::vector<serverTuple>)
{
	
}

Lobby::Lobby(sf::RenderWindow& rw):rw(rw)
{
	font.loadFromFile("DroidSansMono.ttf");

	sf::RectangleShape button;
	button.setSize(sf::Vector2f(200, 50));
	button.setFillColor(sf::Color::Red);
	button.setOrigin(button.getSize().x / 2, button.getSize().y / 2);
	button.setPosition(sf::Vector2f(0, 0));
	buttons.push_back(button);

	sf::Text text;
	text.setFont(font);
	text.setString("Hello");
	text.setPosition(button.getPosition());
	text.setCharacterSize(20);
	text.setColor(sf::Color::Blue);	
	texts.push_back(text);

}


Lobby::~Lobby()
{
}
