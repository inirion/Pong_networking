#pragma once
#include <SFML\Network.hpp>
#include "Networking.h"
#include "Config.h"
#include <iostream>

class Server : public Networking<sf::TcpSocket>
{
private:
	sf::Packet packet;
	sf::TcpListener listener;

public:
	bool setConnection();

	bool Send(sf::Packet)override;
	bool Recive() override;
	inline sf::Packet getPacket() { return packet; };
	Server();
	~Server();
};