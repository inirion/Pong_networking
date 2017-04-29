#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include "Client.h"
#include "Config.h"

using namespace std;

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong pong(window);
	
	char role;
	cin >> role;
	if (role == 'c') {
		Config::isServer = false;
		try {
			Client client(50001,"25.43.221.172" , true);
			
			sf::Packet packet;
			packet << 12;
			client.Send(packet);

			client.Recive();
			int x;
			client.getPacket() >> x;
			cout << x << endl;
		}
		catch (const char *e) {
			cout << e << endl;
		}
	}
	else if (role == 's') {
		Config::isServer = true;
		try {
			Client client(50001, "0.0.0.0", true);
			client.Recive();
			int x;
			client.getPacket() >> x;
			cout << x << endl;

			sf::Packet packet;
			packet << 21;
			client.Send(packet);
		}
		catch (const char *e) {
			cout << e << endl;
		}
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