#pragma once
#include <SFML\Network.hpp>
template <class T>
class Networking
{
protected:
	unsigned short port;
	sf::Packet packet;
	T s;

public:
	virtual bool Send() = 0;
	virtual bool Recive() = 0;

	inline sf::Packet& operator <<(sf::Packet& packet) {
		return this->packet = packet;
	}
	inline sf::Packet& getPacket() {
		return this->packet;
	}

	Networking(const unsigned short port) :port(port) {
	} ;
	~Networking() {};
};
