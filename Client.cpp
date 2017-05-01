#include "Client.h"
#include "Config.h"
void Client::setConnection(sf::IpAddress ip)
{
	this->ip = ip;
	if (Config::isServer) {
		if (listener.listen(port) != sf::Socket::Done)
		{
			throw "Couldn't connect socket =(";
		}
		if (listener.accept(tcpSocket) != sf::Socket::Done)
		{
			throw "Couldn't connect socket =(";
		}
	}
	else {
		sf::Socket::Status status = tcpSocket.connect(ip, port);
		if (status != sf::Socket::Done) {
			throw "Couldn't connect socket =(";
		}
	}
	tcpSocket.setBlocking(false);
}
sf::Socket::Status Client::Send(sf::Packet packet)
{
	return tcpSocket.send(packet);
}

sf::Socket::Status Client::Recive()
{
	return tcpSocket.receive(packet);
}

 Client::Client():port(50001)
{
}

 Client::~Client()
{
	 
}
