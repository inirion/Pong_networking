#include "Broadcaster.h"
#include <iostream>

Broadcaster::Broadcaster(unsigned short broadcastPort, const std::string &serverName) : broadcastPort(broadcastPort), serverName(serverName)
{
	if (s.bind(broadcastPort) != sf::UdpSocket::Done) {
		throw "Coudn't bind broadcast socket";
	}
	else {
		s.setBlocking(false);
	}
}

serverPair Broadcaster::onNewConnection()
{
	// TODO: insert return statement here
	sf::Packet p;
	sf::IpAddress incomingConnectionAddress;
	unsigned short port;
	switch (s.receive(p, incomingConnectionAddress, port)) {
	case sf::Socket::Done : {
		serverPair newP;
		newP.first = incomingConnectionAddress;
		p >> newP.second;
		return newP;
	}
	case sf::UdpSocket::Error: {
		throw "Error occured during broadcasting";
		s.unbind();
		break;
	}
	}
	return serverPair("","");
}

std::vector<serverPair>& Broadcaster::getAllConnections()
{
	serverPair fresh = onNewConnection();
	bool shouldAdd = true;
	if (fresh.first != "") {
		for (serverPair p : conns) {
			if (p.first == fresh.first) {
				shouldAdd = false;
				break;
			}
		}
		if (shouldAdd) {
			conns.push_back(fresh);
		}
	}
	return conns;
}

void Broadcaster::broadcast()
{ 
	sf::Packet p;
	p << serverName;
	switch (s.send(p, sf::IpAddress::Broadcast, broadcastPort)) {
		case sf::UdpSocket::Done: {
			break;
		}
		case sf::UdpSocket::Error: {
			throw "Error occured during broadcasting";
			s.unbind();
			break;
		}
	}
}

Broadcaster::~Broadcaster()
{

}
