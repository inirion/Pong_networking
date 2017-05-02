#include "Lobby.h"
#include <iostream>

void Lobby::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto btn : btns) {
		target.draw(std::get<ConnectionFields::BUTTON>(btn));
		target.draw(std::get<ConnectionFields::TEXT>(btn));
	}
	for (auto btn : paginationBttns) {
		target.draw(std::get<ConnectionFields::BUTTON>(btn));
		target.draw(std::get<ConnectionFields::TEXT>(btn));
	}
}

void Lobby::update(std::vector<serverTuple>,sf::Event e)
{
	isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2i pos = sf::Mouse::getPosition(rw);
	if (e.type == sf::Event::MouseButtonReleased) {
		isPressed = true;
		for (int i = pageNumber*5, j = 0; i < btns.size(), j<5; i++,j++) {
			if (sf::Mouse::getPosition(rw).x > std::get<ConnectionFields::BUTTON>(btns[i]).getPosition().x &&
				sf::Mouse::getPosition(rw).x < std::get<ConnectionFields::BUTTON>(btns[i]).getPosition().x + std::get<ConnectionFields::BUTTON>(btns[i]).getSize().x &&
				sf::Mouse::getPosition(rw).y > std::get<ConnectionFields::BUTTON>(btns[i]).getPosition().y &&
				sf::Mouse::getPosition(rw).y < std::get<ConnectionFields::BUTTON>(btns[i]).getPosition().y + std::get<ConnectionFields::BUTTON>(btns[i]).getSize().y
				) {
				//selected item on list
			}
		}
		for (auto btn : paginationBttns) {
			if (sf::Mouse::getPosition(rw).x > std::get<ConnectionFields::BUTTON>(btn).getPosition().x &&
				sf::Mouse::getPosition(rw).x < std::get<ConnectionFields::BUTTON>(btn).getPosition().x + std::get<ConnectionFields::BUTTON>(btn).getSize().x &&
				sf::Mouse::getPosition(rw).y > std::get<ConnectionFields::BUTTON>(btn).getPosition().y &&
				sf::Mouse::getPosition(rw).y < std::get<ConnectionFields::BUTTON>(btn).getPosition().y + std::get<ConnectionFields::BUTTON>(btn).getSize().y
				) {
				if (std::get<ConnectionFields::TEXT>(btn).getString() == "Next") {
					pageNumber < btns.size()/5 ? pageNumber++ : pageNumber = pageNumber;
					std::cout << pageNumber << std::endl;
				}
				else {
					pageNumber > 0 ? pageNumber-- : pageNumber = pageNumber;
					std::cout << pageNumber << std::endl;
				}
				
			}
		}
		sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x + 1, sf::Mouse::getPosition().y));
		sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x - 1, sf::Mouse::getPosition().y));
	}
}

Lobby::Lobby(sf::RenderWindow& rw):rw(rw)
{
	font.loadFromFile("DroidSansMono.ttf");
	pageNumber = 0;
	sf::RectangleShape button;
	sf::Text text;
	float buttonHeight = rw.getSize().x/5 -40 ;
	float buttonWigth = 200;
	for (int i = 0, j = 0; i < 40; i++, j++) {
		if (j == 5) j = 0;
		button.setOutlineThickness(2.f);
		button.setSize(sf::Vector2f(buttonWigth,buttonHeight));
		button.setFillColor(sf::Color::Red);
		button.setPosition(sf::Vector2f(0, j*buttonHeight));

		text.setFont(font);
		text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
		text.setString("Hello");
		text.setCharacterSize(20);
		text.setColor(sf::Color::Blue);

		btns.push_back(std::make_tuple(button, text));
	}

	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(buttonWigth, buttonHeight));
	button.setFillColor(sf::Color::Red);
	button.setPosition(sf::Vector2f(buttonWigth,rw.getSize().y-buttonHeight ));

	text.setFont(font);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
	text.setString("Prev");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Blue);
	paginationBttns.push_back(std::make_tuple(button, text));
	///
	button.setOutlineThickness(2.f);
	button.setSize(sf::Vector2f(buttonWigth, buttonHeight));
	button.setFillColor(sf::Color::Red);
	button.setPosition(sf::Vector2f(rw.getSize().x - buttonWigth, rw.getSize().y - buttonHeight));

	text.setFont(font);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
	text.setString("Next");
	text.setCharacterSize(20);
	text.setColor(sf::Color::Blue);
	paginationBttns.push_back(std::make_tuple(button, text));
}


Lobby::~Lobby()
{
}
