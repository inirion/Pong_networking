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
//interrface z read packet.
//inna konstrukcja wysy�anych pakiet�w ---> enum 1 or 2 and position example : 1 12,1 15,3 or 2 12,2 15,5 11,1 23,3 first is player position if header is 2 else ball is first.
//odbicie lustrzane pi�ki (gracz zawsze z lewej strony przeciwnik z prawej).
//interpolacja pi�ki.
//refaktoryzacja kodu.
//implementacja do projektu.
//rozbicie Client na 2 osobne klasy (server-client), unieknięcie mieszania logiki klient server
//Dokończenie implementacji metod z klasy generycznej Networking 
//REFAKTOR
// Przy polaczeniu TCP -> opcja powrotu do lobby i stworzenia serwera / nasluchiwania jako klient
// Spawnowanie n-child processow dla testów

int main(int argc, char* argv[]) {

	NetworkManager nm;

	sf::Vector2f(2, 2);
	sf::RenderWindow window(sf::VideoMode(800,600), "TCP TEST", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	Pong *pong;
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
		else {
			if (Config::isServer) {
				std::string name;
				std::cout << "wpisz jakiegos stringa" << std::endl;
				cin >> name;
				sf::Packet p;
				p << name;
				if (s.Send(p)) std::cout << "Wysłano" << std::endl;
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
		else {
			l.update(e);
			window.draw(l);
		}
		
		window.display();
	}
	return 0;
}