#include "Broadcaster.h"
#include <iostream>

void Broadcaster::update()
{
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
	std::vector<serverPair> copy(conns);
	serverPair fresh = onNewConnection();
	bool shouldAdd = true;
	if (fresh.first != "") {
		for (serverPair p : copy) {
			if (p.first == fresh.first) {
				shouldAdd = false;
				break;
			}
		}
		if (shouldAdd) {
			copy.push_back(fresh);
		}
	}
	if (conns != copy) {
		conns = copy;
		return true;
	}
	else {
		return false;
	}
}

void Broadcaster::printConns()
{
	for (auto conn : conns) {
		std::cout << conn.first << " " << conn.second << std::endl;
	}
	std::system(CLEAR);
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


void Broadcaster::broadcast(STATES e)
{ 
	sf::Packet p;
	p << (char)e << serverName;
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
