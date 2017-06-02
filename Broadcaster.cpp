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


Broadcaster::Broadcaster( const std::string &serverName) : serverName(serverName), Networking<sf::UdpSocket>(Config::port)

{
	if (socket.bind(Config::port) != sf::UdpSocket::Done) {
		throw "Coudn't bind broadcast socket";
	}
	else {
		lastFrameTime = Config::clock.getElapsedTime().asMilliseconds();
		socket.setBlocking(false);
	}
}

bool Broadcaster::checkNewConn()
{
	bool reset = false;
	serverTuple fresh = onNewConnection();
	bool shouldAdd = true;
	if (std::get<TupleFields::STATE>(fresh) >= STATES::FAILED) {
		reset = false;
		shouldAdd = false;
	}
	if (conns.size() == 0 && std::get<TupleFields::STATE>(fresh) == STATES::EXIT) {
		reset =  false;
		shouldAdd = false;
	}
	for (size_t i = 0; i < conns.size(); i++) {
		if (std::get<TupleFields::IPADRESS>(conns[i]) == std::get<TupleFields::IPADRESS>(fresh)) {
			std::get<TupleFields::TIMESTAMP>(conns[i]) = mticks();
			shouldAdd = false;
			if (std::get<TupleFields::STATE>(fresh) == STATES::EXIT || (int)std::get<TupleFields::STATE>(fresh) > 2) {
				conns.erase(conns.begin() + i);
				reset = true;
			}
		}
	}
	
  
	for (size_t i = 0; i < conns.size(); i++) {
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
	sf::Packet p;
	if (Recive(p)) {
		int ENUM;
		std::string name;
		p >> ENUM >> name;
		return std::make_tuple(incomingConnectionAddress, name, (STATES)ENUM, mticks());
	}

	else {
		return std::make_tuple("0.0.0.0", "", STATES::FAILED, Config::clock.getElapsedTime().asMilliseconds());
	}
}

bool Broadcaster::Recive(sf::Packet& packet)
{
	unsigned short port;
	if (socket.receive(packet, incomingConnectionAddress, port) == sf::UdpSocket::Done) {
		if (incomingConnectionAddress == sf::IpAddress("0.0.0.0")) return false;
		else return true;
	}
}


void Broadcaster::broadcast(STATES ENUM)
{ 
	sf::Packet p;
	p << (int)ENUM << serverName;
	Send(p);
}

bool Broadcaster::Send(sf::Packet p)
{
	if (socket.send(p, "25.255.255.255", Config::port) == sf::UdpSocket::Done) return true;
	else return false;

}

Broadcaster::~Broadcaster()
{
	broadcast(STATES::EXIT);
}
