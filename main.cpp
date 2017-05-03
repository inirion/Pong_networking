#include <iostream>
#include <SFML/Network.hpp>
#include "Pong.h"
#include "Client.h"
#include "Config.h"
#include "Broadcaster.h"
#include "Server.h"
#include "Lobby.h"

using namespace std;
//interrface z read packet.
//inna konstrukcja wysy�anych pakiet�w ---> enum 1 or 2 and position example : 1 12,1 15,3 or 2 12,2 15,5 11,1 23,3 first is player position if header is 2 else ball is first.
//odbicie lustrzane pi�ki (gracz zawsze z lewej strony przeciwnik z prawej).
//interpolacja pi�ki.
//refaktoryzacja kodu.
//implementacja do projektu.
//rozbicie Client na 2 osobne klasy (server-client), unieknięcie mieszania logiki klient server
//Dokończenie implementacji metod z klasy generycznej Networking 
//REFAKTOR
int main(int argc, char* argv[]) {
	sf::Vector2f(2, 2);
	sf::RenderWindow window(sf::VideoMode(800,600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong *pong;
	Client c;
	Server s;
	Broadcaster *b;
	char role;
	cin >> role;

	
	if (role == 's') {

		Config::isServer = true;

		std::string serverName;
		cout << "Enter server name: ";
		cin >> serverName;

		try {
			b = new Broadcaster(serverName);
		}
		catch (const char *e) {
			cout << e << endl;
		}
		
	}
	else {
		b = new Broadcaster();
		Config::isServer = false;
	}

	/*
	// TODO: clients should be created depending on ip returned from broadcaster
	if (role == 'c') {
		Config::isServer = false;
		try {
			//25.75.100.22
			//25.43.221.172
			c = new Client(50001, "25.43.221.172");
		}
		catch (const char *e) {
			cout << e << endl;
		}
		pong = new Pong(window, *c);
	}
	else if (role == 's') {
		Config::isServer = true;
		try {
			c = new Client(50001, "0.0.0.0");
		}
		catch (const char *e) {
			cout << e << endl;
		}
		pong = new Pong(window, *c);
	}
	
	*/
	Lobby l(window);
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
			b->update();
			if (Config::isServer) {
				Config::TCPstart = s.setConnection();
			}
			else {
				Config::TCPstart = c.setConnection(l.getSelectedIpAdress());
			}
			l.update(b->getConns(), e);
			window.draw(l);
		}
		else {
			if (Config::isServer) {
				int name;
				cin >> name;
				sf::Packet p;
				p << name;
				s.Send(p);
			}
			else {
				if(c.Recive()) {
					std::string a;
					c.getPacket() >> a;
					std::cout << a << std::endl;
				}
				}	
			}
		
		if (Config::isPongPlaying) {
			pong->update();
			window.draw(*pong);
		}
		
		window.display();
	}
	delete b;
	return 0;
}