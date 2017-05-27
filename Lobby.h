#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Broadcaster.h"
#include "Server.h"
#include "Client.h"



#define ButtonPosition(btn) (std::get<Fields::BUTTON>(btn).getPosition())
#define ButtonSize(btn) (std::get<Fields::BUTTON>(btn).getSize())
#define ButtonText(btn) (std::get<Fields::TEXT>(btn).getString().toAnsiString())
#define ButtonIP(btn) (std::get<Fields::IP>(btn))
#define ButtonVisability(btn) (std::get<Fields::VISIBILITY>(btn))
#define Button(btn) (std::get<Fields::BUTTON>(btn))
#define Text(btn) (std::get<Fields::TEXT>(btn))

#define PlayButtonVisability(btn) (std::get<Fields::VISIBILITY>(btn))
#define PlayButton(btn) (std::get<Fields::BUTTON>(btn))
#define PlayText(btn) (std::get<Fields::TEXT>(btn))

using ConnectionButton = std::tuple<sf::RectangleShape, sf::Text,bool,sf::IpAddress>;
using ButtonTuple = std::tuple<sf::RectangleShape, sf::Text, bool>;

enum Fields { BUTTON, TEXT, VISIBILITY, IP };

class Lobby:public sf::Drawable
{
private:
	unsigned short pageNumber;
	sf::IpAddress SelectedIP;
	int yOffest;
	float buttonHeight;
	float buttonWidth;
	sf::RenderWindow& rw;
	sf::Font font;

	void EnableButton();
	bool InButtonBounds(sf::RectangleShape btn);
	ConnectionButton AddButton(std::string name = "a", sf::IpAddress adress = "0.0.0.0", float x = -1, float y= -1);
	ButtonTuple AddButton(std::string name,  float x, float y);
	void FillButtonList(std::vector<serverTuple>);

	std::vector<ConnectionButton> paginationBttns;
	std::vector<ConnectionButton> btns;
	ConnectionButton refreshBtn;
	ButtonTuple playBtn;
public:
	Broadcaster *b;
	void SendStartButtonClick(sf::Event e, Client &c, Server &s);
	void GetStartButtonClick(sf::Event e, Client &c, Server &s);
	inline void PlayButtonVisible(bool t) { PlayButtonVisability(playBtn) = t; }
	inline sf::IpAddress getSelectedIpAdress() { return SelectedIP; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Event e);
	Lobby(sf::RenderWindow& rw, std::string name);
	~Lobby();
};

