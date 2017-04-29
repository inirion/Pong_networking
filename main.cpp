#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include "Client.h"
#include "Config.h"

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong *pong;
	Client *c;
	char role;
	cin >> role;
	if (role == 'c') {
		Config::isServer = false;
		try {
			//25.75.100.22
			//25.43.221.172
			c = new Client(50001,"25.75.100.22" , true);
		}
		catch (const char *e) {
			cout << e << endl;
		}
		pong = new Pong(window, *c);
	}
	else if (role == 's') {
		Config::isServer = true;
		try {
			c = new Client(50001, "0.0.0.0", true);
		}
		catch (const char *e) {
			cout << e << endl;
		}
		pong = new Pong(window, *c);
	}
	
	
	
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
		pong->update();
		window.clear(sf::Color(255, 255, 255));
		window.draw(*pong);
		window.display();

	}
	return 0;
}