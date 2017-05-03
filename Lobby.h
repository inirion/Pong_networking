#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics.hpp>
#include "Broadcaster.h"

#define ButtonPosition(btn) (std::get<ConnectionFields::BUTTON>(btn).getPosition())
#define ButtonSize(btn) (std::get<ConnectionFields::BUTTON>(btn).getSize())
#define ButtonText(btn) (std::get<ConnectionFields::TEXT>(btn).getString().toAnsiString())
#define ButtonIP(btn) (std::get<ConnectionFields::IP>(btn))
#define ButtonVisability(btn) (std::get<ConnectionFields::VISIBILITY>(btn))
#define Button(btn) (std::get<ConnectionFields::BUTTON>(btn))
#define Text(btn) (std::get<ConnectionFields::TEXT>(btn))

using ConnectionButtons = std::tuple<sf::RectangleShape, sf::Text,bool,sf::IpAddress>;
enum ConnectionFields { BUTTON, TEXT, VISIBILITY, IP };

class Lobby:public sf::Drawable
{
private:
	unsigned short pageNumber;
	sf::IpAddress SelectedIP;
	float yOffest;
	float buttonHeight;
	float buttonWidth;
	sf::RenderWindow& rw;
	sf::Font font;

	void EnableButton();
	bool InButtonBounds(ConnectionButtons btn);
	ConnectionButtons AddButton(std::string name = "a", sf::IpAddress adress = "0.0.0.0", float x = -1, float y= -1);
	void FillButtonList(std::vector<serverTuple>);

	std::vector<ConnectionButtons> paginationBttns;
	std::vector<ConnectionButtons> btns;
public:
	inline sf::IpAddress getSelectedIpAdress() { return SelectedIP; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(std::vector<serverTuple>,sf::Event e);
	Lobby(sf::RenderWindow& rw);
	~Lobby();
};

