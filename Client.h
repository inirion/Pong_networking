#pragma once
#include <SFML/Network.hpp>
#include "Networking.h"
#include <iostream>

class Client : public Networking<sf::TcpSocket>
{
private:
	sf::IpAddress ip;
public:
	bool setConnection(sf::IpAddress);
	bool Send(sf::Packet)override;
	bool Recive() override;
	Client();
	~Client();
};