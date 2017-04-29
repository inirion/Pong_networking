#include <iostream>
#include <SFML\Network.hpp>
#include "Pong.h"
#include "Client.h"
#include "Config.h"

using namespace std;
//todo broadcast na udp (server list).
//interrface z read packet.
//inna konstrukcja wysy³anych pakietów ---> enum 1 or 2 and position example : 1 12,1 15,3 or 2 12,2 15,5 11,1 23,3 first is player position if header is 2 else ball is first.
//odbicie lustrzane pi³ki (gracz zawsze z lewej strony przeciwnik z prawej).
//prze³¹czenie miêdzy UDP a TCP po znajdzieniu IP z brounkasta.
//interpolacja pi³ki.
//refaktoryzacja kodu.
//implementacja do projektu.
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
			c = new Client(50001,"25.43.221.172" , true);
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