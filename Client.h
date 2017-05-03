#pragma once
#include <SFML\Network.hpp>
#include <iostream>

class Client 
{
private:
	sf::Packet packet;
	unsigned short port;
	sf::IpAddress ip;
	sf::TcpListener listener;
	sf::TcpSocket tcpSocket;
public:
	bool setConnection(sf::IpAddress = "0.0.0.0");
	sf::Socket::Status Send(sf::Packet packet);
	sf::Socket::Status Recive();
	inline sf::Packet getPacket() { return packet; };
	Client();
	~Client();
};