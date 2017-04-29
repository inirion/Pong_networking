#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include "Client.h"

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong pong(window);

	try {
		Client client(50001, "25.75.100.22",true);
		client.Send(sf::Packet());
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