#pragma once
#include <SFML\Network.hpp>
#include <iostream>
#include <type_traits>

template <class type>
class Client 
{
private:
	bool tcp;
	unsigned short port;
	sf::IpAddress ip;
	type socket;
public:
	bool Send(sf::Packet packet);
	sf::Packet Recive();
	Client(unsigned short port, sf::IpAddress ip);
	~Client();
};

template<class type>
inline bool Client<type>::Send(sf::Packet packet)
{
	return false;
}

template<class type>
inline sf::Packet Client<type>::Recive()
{
	return sf::Packet();
}

template<class type>
inline Client<type>::Client(unsigned short port, sf::IpAddress ip): port(port), ip(ip)
{
	if (std::is_same<type, sf::UdpSocket>::value) {
		std::cout << " udp " << std::endl;
		tcp = false;
	}
	if (std::is_same<type, sf::TcpSocket>::value){
		std::cout << " tcp " << std::endl;
		tcp = true;
		sf::Socket::Status status = socket.connect(ip, port);
		if (status != sf::Socket::Done) {
			throw "Couldn't connect socket =(";
		}
	}
}

template<class type>
inline Client<type>::~Client()
{
}
