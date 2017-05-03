#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics.hpp>
#include "Broadcaster.h"

using ConnectionButtons = std::tuple<sf::RectangleShape, sf::Text,bool>;
enum ConnectionFields { BUTTON, TEXT, VISIBILITY };

class Lobby:public sf::Drawable
{
private:
	unsigned short pageNumber;
	bool isPressed;
	void EnableButton();
	float yOffest;
	float buttonHeight;
	float buttonWidth;
	bool InButtonBounds(ConnectionButtons btn);
	ConnectionButtons AddButton(float x = -1, float y= -1,std::string name = "a");
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

