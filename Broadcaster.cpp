#include "Broadcaster.h"
#include <iostream>

void Broadcaster::update()
{
	// TODO: every N secs check if you've received packed from already contained connections
	if (Config::isServer) {
		broadcast(STATES::BROADCASTING);
	}
	else {
		if (checkNewConn()) {
			printConns();
		}
	}
}



Broadcaster::Broadcaster(unsigned short broadcastPort, const std::string &serverName) : broadcastPort(broadcastPort), serverName(serverName)
{
	if (s.bind(broadcastPort) != sf::UdpSocket::Done) {
		throw "Coudn't bind broadcast socket";
	}
	else {
		s.setBlocking(false);
	}
}

bool Broadcaster::checkNewConn()
{
	serverTuple fresh = onNewConnection();
	bool shouldAdd = true;
	if (std::get<TupleFields::STATE>(fresh) == STATES::FAILED) {
		return false;
	}
	if (conns.size() == 0 && std::get<TupleFields::STATE>(fresh) == STATES::EXIT) {
		return false;
	}
	if (conns.size() > 0) {
		for (int i = 0; i < conns.size(); i++) {
			if (std::get<TupleFields::IPADRESS>(conns[i]) == std::get<TupleFields::IPADRESS>(fresh)) {
				shouldAdd = false;
				if (std::get<TupleFields::STATE>(fresh) == STATES::EXIT || (int)std::get<TupleFields::STATE>(fresh) > 2) {
					conns.erase(conns.begin() + i);

					return true;
				}
				break;
			}
		}
	}
	
	if (shouldAdd) {
		conns.push_back(fresh);
		return true;
	}
	return false;
}


void Broadcaster::printConns()
{
	std::system(CLEAR);
	for (auto conn : conns) {
		std::cout << std::get<TupleFields::IPADRESS>(conn) << " " << std::get<TupleFields::NAME>(conn) << std::endl;
	}
}

serverTuple Broadcaster::onNewConnection()
{
	// TODO: insert return statement here
	sf::Packet p;
	sf::IpAddress incomingConnectionAddress;
	unsigned short port;
	switch (s.receive(p, incomingConnectionAddress, port)) {
	case sf::Socket::Done : {
		int ENUM;
		std::string name;
		p >> ENUM >> name;
		return std::make_tuple(incomingConnectionAddress, name, (STATES)ENUM);
	}
	case sf::UdpSocket::Error: {
		throw "Error occured during broadcasting";
		s.unbind();
		break;
	}
	}
	return std::make_tuple(incomingConnectionAddress, "", STATES::FAILED);
}



void Broadcaster::broadcast(STATES ENUM)
{ 
	sf::Packet p;
	p << (int)ENUM << serverName;
	switch (s.send(p, "25.255.255.255", broadcastPort)) {
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
	broadcast(STATES::EXIT);
}
