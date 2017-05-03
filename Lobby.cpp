#include "Lobby.h"
#include <iostream>



void Lobby::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto btn : btns) {
		if (ButtonVisability(btn)) {
			target.draw(Button(btn));
			target.draw(Text(btn));
		}
	}
	for (auto btn : paginationBttns) {
		if(ButtonVisability(btn)) {
			target.draw(Button(btn));
			target.draw(Text(btn));
		}
	}
}

bool Lobby::InButtonBounds(ConnectionButtons btn) {
	if (sf::Mouse::getPosition(rw).x > ButtonPosition(btn).x &&
		sf::Mouse::getPosition(rw).x < ButtonPosition(btn).x + ButtonSize(btn).x &&
		sf::Mouse::getPosition(rw).y > ButtonPosition(btn).y &&
		sf::Mouse::getPosition(rw).y < ButtonPosition(btn).y + ButtonSize(btn).y
		) return true;
	return false;
}

void Lobby::update(std::vector<serverTuple> connections,sf::Event e)
{
	FillButtonList(connections);

	if (e.type == sf::Event::MouseButtonReleased) {
		for (auto btn : btns) {
			if (ButtonVisability(btn)) {
				if (InButtonBounds(btn)) {
					std::cout << ButtonText(btn) << std::endl;
				}
			}
		}
		for (auto btn : paginationBttns) {
			if (ButtonVisability(btn)) {
				if (InButtonBounds(btn)) {
					if (ButtonText(btn) == "Next") {
						pageNumber++;
						std::cout << ButtonText(btn) << std::endl;
						EnableButton();
					}
					else {
						pageNumber--;
						std::cout << ButtonText(btn) << std::endl;
						EnableButton();
					}
				}
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

	pageNumber == 1 ? ButtonVisability(paginationBttns[0]) = false : ButtonVisability(paginationBttns[0]) = true;
	pageNumber*5 >= (btns.size()) ? ButtonVisability(paginationBttns[1]) = false : ButtonVisability(paginationBttns[1]) = true;
}

Lobby::Lobby(sf::RenderWindow& rw):rw(rw)
{
	font.loadFromFile("DroidSansMono.ttf");
	pageNumber = 1;
	yOffest = 0;
	buttonWidth = 200;
	buttonHeight = rw.getSize().x / 5 - 40;

	for (int i = 0, j = 0; i < 1; i++, j++) {
		btns.push_back(AddButton(std::to_string(i) ,"0.0.0.0", -1,-1));
	}
	paginationBttns.push_back(AddButton("Prev","0.0.0.0", buttonWidth, rw.getSize().y - buttonHeight));
	paginationBttns.push_back(AddButton("Next","0.0.0.0", rw.getSize().x - buttonWidth, rw.getSize().y - buttonHeight));
	EnableButton();
}

void Lobby::FillButtonList(std::vector<serverTuple> connections) {
	
}

ConnectionButtons Lobby::AddButton(std::string name, sf::IpAddress adress, float x, float y) {
	sf::RectangleShape button;
	sf::Text text;

	(int)yOffest % 5 == 0 ? yOffest = 0 : yOffest= yOffest;

	x == -1 ? x = 0: x = x;
	y == -1 ? y = yOffest*buttonHeight : y = y;

	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	button.setFillColor(sf::Color::Red);
	button.setPosition(sf::Vector2f(x, y));

	text.setFont(font);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
	text.setString(name);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Blue);
	
	yOffest++;

	return std::make_tuple(button, text, false, adress);
}

Lobby::~Lobby()
{
}