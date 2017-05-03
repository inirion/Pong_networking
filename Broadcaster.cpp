#include "Broadcaster.h"
#include <iostream>

double mticks()
{
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<float, std::milli> duration;

	static clock::time_point start = clock::now();
	duration elapsed = clock::now() - start;
	return elapsed.count();
}

void Broadcaster::update()
{
	// TODO: every N secs check if you've received packed from already contained connections
	if (Config::clock.getElapsedTime().asMilliseconds() - lastFrameTime >= 1) {
		if (Config::isServer) {
			broadcast(STATES::BROADCASTING);
		}
		else {
			if (checkNewConn()) {
				printConns();
			}
		}
		lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
	}
}

void Broadcaster::close()
{
	broadcast(STATES::EXIT);
}

std::vector<serverTuple> Broadcaster::getConns()
{
	return conns;
}

Broadcaster::Broadcaster(unsigned short broadcastPort, const std::string &serverName) : broadcastPort(broadcastPort), serverName(serverName)
{
	if (s.bind(broadcastPort) != sf::UdpSocket::Done) {
		throw "Coudn't bind broadcast socket";
	}
	else {
		//conns.push_back(std::make_tuple("0.0.0.0", "asd", STATES::FAILED, Config::clock.getElapsedTime().asMilliseconds()));
		lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
		s.setBlocking(false);
	}
}

bool Broadcaster::checkNewConn()
{
	bool reset = false;
	serverTuple fresh = onNewConnection();
	bool shouldAdd = true;
	if (std::get<TupleFields::STATE>(fresh) == STATES::FAILED) {
		reset = false;
		shouldAdd = false;
	}
	if (conns.size() == 0 && std::get<TupleFields::STATE>(fresh) == STATES::EXIT) {
		reset =  false;
		shouldAdd = false;
	}
	for (int i = 0; i < conns.size(); i++) {
		
		if (std::get<TupleFields::IPADRESS>(conns[i]) == std::get<TupleFields::IPADRESS>(fresh)) {
			
			std::get<TupleFields::TIMESTAMP>(conns[i]) = mticks();
			shouldAdd = false;
			if (std::get<TupleFields::STATE>(fresh) == STATES::EXIT || (int)std::get<TupleFields::STATE>(fresh) > 2) {
				conns.erase(conns.begin() + i);
				reset = true;
			}
		}
	}
	
	
	for (int i = 0; i < conns.size(); i++) {
		if (mticks() - std::get<TupleFields::TIMESTAMP>(conns[i]) > 5000) {
			conns.erase(conns.begin() + i);
			reset = true;
		}
	}

	if (shouldAdd) {
		conns.push_back(fresh);
		reset = true;
	}
	return reset;
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
		
		if (incomingConnectionAddress == sf::IpAddress("0.0.0.0")) {
			return std::make_tuple(incomingConnectionAddress, "", STATES::FAILED, Config::clock.getElapsedTime().asMilliseconds());
		}
		
		int ENUM;
		std::string name;
		p >> ENUM >> name;
		return std::make_tuple(incomingConnectionAddress, name, (STATES)ENUM, mticks());
	}
	case sf::UdpSocket::Error: {
		
		throw "Error occured during broadcasting";
		s.unbind();
		break;
	}
	}
	
	return std::make_tuple(incomingConnectionAddress, "", STATES::FAILED, Config::clock.getElapsedTime().asMilliseconds());
}


void Broadcaster::broadcast(STATES ENUM)
{ 
	sf::Packet p;
	p << (int)ENUM << serverName;
	//25.75.100.22
		//25.255.255.255
	switch (s.send(p, "25.255.255.255", broadcastPort)) {
		case sf::UdpSocket::Done: {
			std::cout << "asdasd" << std::endl;
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
