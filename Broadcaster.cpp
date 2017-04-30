#include "Broadcaster.h"

Broadcaster::Broadcaster(unsigned short broadcast_port, const std::string &serverName) : broadcastPort(broadcastPort), serverName(serverName)
{
	if (s.bind(broadcast_port) != sf::UdpSocket::Done) {
		throw "Coudn't bind broadcast socket";
	}
	else {
		s.setBlocking(false);
	}
}

serverPair& Broadcaster::onNewConnection()
{
	// TODO: insert return statement here
	sf::Packet p;
	sf::IpAddress incomingConnectionAddress;
	switch (s.receive(p, incomingConnectionAddress, broadcastPort)) {
	case sf::UdpSocket::Done: {
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
}

std::vector<serverPair>& Broadcaster::getAllConnections()
{
	serverPair * fresh = &onNewConnection();
	bool shouldAdd = true;
	if (fresh) {
		for (serverPair p : conns) {
			if (p.first == fresh->first) {
				shouldAdd = false;
				break;
			}
		}
		if (shouldAdd) {
			conns.push_back(*fresh);
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
