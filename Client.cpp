#include "Client.h"
#include "Config.h"
void Client::setConnection(sf::IpAddress ip)
{
	listener.setBlocking(false);
	tcpSocket.setBlocking(false);
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
		
		std::cout << "Couldn't connect socket =(" << std::endl;
	}
	else {
		sf::Socket::Status status = tcpSocket.connect(ip, port);
		if (status != sf::Socket::Done) {
			throw "Couldn't connect socket =(";
		}
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

 Client::Client():port(50000)
{
}

 Client::~Client()
{
	 
}
