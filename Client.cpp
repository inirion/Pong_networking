#include "Client.h"
#include "Config.h"
bool Client::setConnection(sf::IpAddress ip)
{
	this->ip = ip;
	if (Config::isServer) {
		if (listener.accept(tcpSocket) != sf::Socket::Done)
		{
			return false;
		}
		else {
			return true;
		}
	}
	else {
		sf::Socket::Status status = tcpSocket.connect(ip, port);
		if (status != sf::Socket::Done) {
			return false;
		}
		return true;
	}
	
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
	listener.setBlocking(false);
	tcpSocket.setBlocking(false);
	if (listener.listen(port) != sf::Socket::Done)
	{
		throw "Couldn't connect socket =(";
	}
}

 Client::~Client()
{
	 
}
