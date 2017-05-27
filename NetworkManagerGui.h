#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "NetworkManager.h"
#include <tuple>

template<typename ...Params>
using buttonClickCallback = void(*)(const Params &params ...);

using refreshButton = std::tuple<sf::RectangleShape, sf::Text, bool, buttonClickCallback<>>;
using networkInterfaceButton = std::tuple<sf::RectangleShape, sf::Text, bool, buttonClickCallback<>>;

enum refreshButtonFields { BUTTON, TEXT, VISIBILITY, CALLABACK };
enum networkButtonFields { BUTTON, TEXT, VISIBILITY, CALLABACK };

class NetworkManagerGui : public sf::Drawable
{
private:
	sf::RenderWindow& rw;
	NetworkManager nm;
public:
	NetworkManagerGui(sf::RenderWindow& rw);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Event e);
	~NetworkManagerGui();
};

