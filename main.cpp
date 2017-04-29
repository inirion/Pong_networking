#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include <conio.h>

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "UDP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong pong(window);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			default: break;
			case e.Closed: {
				window.close();
				e.type = e.Count;
			}break;
			}
		}
		pong.update();
		window.clear(sf::Color(255, 255, 255));
		window.draw(pong);
		window.display();

	}
	return 0;
}