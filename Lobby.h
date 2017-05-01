#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics.hpp>
#include "Broadcaster.h"
class Lobby:public sf::Drawable
{
private:
	std::vector<sf::RectangleShape> buttons;
	std::vector<sf::Text> texts;
	sf::RenderWindow& rw;
	sf::Font font;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(std::vector<serverTuple>);
	Lobby(sf::RenderWindow& rw);
	~Lobby();
};

