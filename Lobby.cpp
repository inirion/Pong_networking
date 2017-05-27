#include "Lobby.h"
#include <iostream>



void Lobby::
SendStartButtonClick()
{
}

void Lobby::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (SelectedIP == sf::IpAddress("0.0.0.1") && !Config::isServer)
	{
		for (auto btn : btns) {
			if (ButtonVisability(btn)) {
				target.draw(Button(btn));
				target.draw(Text(btn));
			}
		}
		for (auto btn : paginationBttns) {
			if (ButtonVisability(btn)) {
				target.draw(Button(btn));
				target.draw(Text(btn));
			}
		}

		target.draw(Button(refreshBtn));
		target.draw(Text(refreshBtn));
	}
	else {
		if (PlayButtonVisability(playBtn)) {
			target.draw(PlayButton(playBtn));
			target.draw(PlayText(playBtn));
		}
	}
}


bool Lobby::InButtonBounds(sf::RectangleShape btn) {
	//std::cout << "Mouse x : " << sf::Mouse::getPosition(rw).x << " Mouse Y : " << sf::Mouse::getPosition(rw).y << std::endl;
	//std::cout << "Button x : " << btn.getSize().x << " button Y : " << btn.getSize().y << std::endl;
	if (sf::Mouse::getPosition(rw).x > btn.getPosition().x &&
		sf::Mouse::getPosition(rw).x < btn.getPosition().x + btn.getSize().x &&
		sf::Mouse::getPosition(rw).y > btn.getPosition().y &&
		sf::Mouse::getPosition(rw).y < btn.getPosition().y + btn.getSize().y
		) return true;
	return false;
}

void Lobby::update(sf::Event e)
{
	
	if (!Config::TCPstart) {
		b->update();
	}
	
	if (e.type == sf::Event::MouseButtonReleased) {
		
		for (auto btn : btns) {
			if (ButtonVisability(btn)) {
				if (InButtonBounds(Button(btn))) {
					SelectedIP = ButtonIP(btn);
					PlayButtonVisible();
				}
			}
		}
		
		for (auto btn : paginationBttns) {
			if (ButtonVisability(btn)) {
				if (InButtonBounds(Button(btn))) {
					if (ButtonText(btn) == "Next") {
						pageNumber++;
						EnableButton();
					}
					else if(ButtonText(btn) == "Prev") {
						pageNumber--;
						EnableButton();
					}
				}
			}
		}
		
		
		if (ButtonVisability(refreshBtn)) {
			
			if (InButtonBounds(Button(refreshBtn))) {
				std::cout << "sad" << std::endl;
				FillButtonList(b->getConns());
				
			}
		}
		sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x + 1, sf::Mouse::getPosition().y));
		sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x - 1, sf::Mouse::getPosition().y));
	}
}

void Lobby::EnableButton() {

	for (int i = 0; i < btns.size(); i++) {
		ButtonVisability(btns[i]) = false;
	}

	for (int i = (pageNumber - 1) * 5, j = 0; i < btns.size() && j < 5; i++, j++) {
		ButtonVisability(btns[i]) = true;
	}

	ButtonVisability(refreshBtn) = true;

	pageNumber == 1 ? ButtonVisability(paginationBttns[0]) = false : ButtonVisability(paginationBttns[0]) = true;
	pageNumber*5 >= (btns.size()) ? ButtonVisability(paginationBttns[1]) = false : ButtonVisability(paginationBttns[1]) = true;
}

Lobby::Lobby(sf::RenderWindow& rw, std::string name):rw(rw)
{
	if(Config::isServer)
		b = new Broadcaster(name);
	else
		b = new Broadcaster();

	font.loadFromFile("DroidSansMono.ttf");
	pageNumber = 1;
	yOffest = 0;
	buttonWidth = 200;
	buttonHeight = rw.getDefaultView().getSize().y / 5;
	SelectedIP = sf::IpAddress("0.0.0.1");

	paginationBttns.push_back(AddButton("Prev","", buttonWidth, rw.getSize().y - buttonHeight));
	paginationBttns.push_back(AddButton("Next","", rw.getSize().x - buttonWidth, rw.getSize().y - buttonHeight));
	refreshBtn = AddButton("Refresh", "", rw.getSize().x - buttonWidth, 0);
	EnableButton();
	playBtn = AddButton("Play", rw.getSize().x - buttonWidth, rw.getSize().y- buttonHeight);
	if (Config::isServer) PlayButtonVisible();
}

void Lobby::FillButtonList(std::vector<serverTuple> connections) {
	btns.clear();
	yOffest = 0;
	for (auto connection : connections) {
		btns.push_back(AddButton(ConnectionText(connection), ConnectionIP(connection)));
	}
	EnableButton();
}

ConnectionButton Lobby::AddButton(std::string name, sf::IpAddress adress, float x, float y) {
	sf::RectangleShape button;
	sf::Text text;

	yOffest % 5 == 0 ? yOffest = 0 : yOffest= yOffest;
	x == -1 ? x = 0: x = x;
	y == -1 ? y = yOffest*buttonHeight : y = y;
	x == 0 ? yOffest++ : yOffest = yOffest ;

	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	button.setFillColor(sf::Color::Red);
	button.setPosition(sf::Vector2f(x, y));

	text.setFont(font);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
	text.setString(name);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);

	return std::make_tuple(button, text, false, adress);
}

ButtonTuple Lobby::AddButton(std::string name, float x, float y) {
	sf::RectangleShape button;
	sf::Text text;

	yOffest % 5 == 0 ? yOffest = 0 : yOffest = yOffest;
	x == -1 ? x = 0 : x = x;
	y == -1 ? y = yOffest*buttonHeight : y = y;
	x == 0 ? yOffest++ : yOffest = yOffest;

	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	button.setFillColor(sf::Color::Red);
	button.setPosition(sf::Vector2f(x, y));

	text.setFont(font);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
	text.setString(name);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);

	return std::make_tuple(button, text, false);
}

Lobby::~Lobby()
{
	delete b;
}
