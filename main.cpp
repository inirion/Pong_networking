#include <iostream>
#include <SFML/Network.hpp>

#include "Pong.h"
#include "Client.h"
#include "Config.h"
#include "Broadcaster.h"
#include "Server.h"
#include "Lobby.h"
#include "NetworkManager.h"

using namespace std;
int main(int argc, char* argv[]) {

	NetworkManager nm;
	sf::RenderWindow window(sf::VideoMode(800,600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong *pong = new Pong(window);
	Client c;
	Server s;
	std::string serverName;
	char role;
	cin >> role;
	if (role == 's') {

		Config::isServer = true;
		cout << "Enter server name: ";
		cin >> serverName;
	}
	else {
		Config::isServer = false;
	}

	Lobby l(window, serverName);
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
		window.clear(sf::Color(255, 255, 255));
		
		if (!Config::TCPstart) {
			if (Config::isServer) {
				Config::TCPstart = s.setConnection();
			}
			else {
				Config::TCPstart = c.setConnection(l.getSelectedIpAdress());
			}
		}
		if (!Config::isPongPlaying) {
			l.update(e,c,s);
			window.draw(l);
		}
		if (Config::isPongPlaying) {
			pong->update(e,c,s);
			window.draw(*pong);
		}
		window.display();
	}
	return 0;
}