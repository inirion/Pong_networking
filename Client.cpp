#include "Client.h"
#include "Config.h"
sf::Socket::Status Client::Send(sf::Packet packet)
{
	return tcpSocket.send(packet);
}

sf::Socket::Status Client::Recive()
{
	return tcpSocket.receive(packet);
}

 Client::Client(unsigned short port, sf::IpAddress ip) : port(port), ip(ip)
{
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

 Client::~Client()
{
}
