#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics.hpp>
#include "Broadcaster.h"

using ConnectionButtons = std::tuple<sf::RectangleShape, sf::Text>;
enum ConnectionFields { BUTTON, TEXT };

class Lobby:public sf::Drawable
{
private:
	unsigned short pageNumber;
	bool isPressed;
	sf::Vector2i MouseClickPos();
	std::vector<ConnectionButtons> paginationBttns;
	std::vector<ConnectionButtons> btns;
	sf::RenderWindow& rw;
	sf::Font font;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(std::vector<serverTuple>,sf::Event e);
	Lobby(sf::RenderWindow& rw);
	~Lobby();
};

