#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include "Client.h"

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "UDP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong pong(window);

	try {
		Client<sf::TcpSocket> client(50001, "127.0.0.1");
	}
	catch (const char *e) {
		cout << e << endl;
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
		pong.update();
		window.clear(sf::Color(255, 255, 255));
		window.draw(pong);
		window.display();

	}
	return 0;
}