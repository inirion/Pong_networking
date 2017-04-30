#pragma once
#include <SFML\Network.hpp>
#include <iostream>

class Client 
{
private:
	sf::Packet packet;
	bool tcp;
	unsigned short port;
	sf::IpAddress ip;
	sf::TcpListener listener;
	sf::TcpSocket tcpSocket;
public:
	sf::Socket::Status Send(sf::Packet packet);
	sf::Socket::Status Recive();
	inline sf::Packet getPacket() { return packet; };
	Client(unsigned short port, sf::IpAddress ip);
	~Client();
};