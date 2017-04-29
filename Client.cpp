#include "Client.h"
#include "Config.h"
sf::Socket::Status Client::Send(sf::Packet packet)
{
	sf::Socket::Status status;
	if(tcp)
		status = tcpSocket.send(packet);
	else
		status = udpSocket.send(packet,ip,port);
	return status;
}

sf::Socket::Status Client::Recive()
{
	sf::Socket::Status status;
	if (tcp)
		status = tcpSocket.receive(packet);
	else {
		sf::IpAddress adress;
		status = udpSocket.receive(packet, adress, port);
	}
		
	return status;
}

 Client::Client(unsigned short port, sf::IpAddress ip, bool isTcp) : port(port), ip(ip)
{
	if (!isTcp) {
		std::cout << " udp " << std::endl;
		tcp = false;
		sf::Socket::Status status = udpSocket.bind(port);
		if (status != sf::Socket::Done) {
			throw "Couldn't connect socket =(";
		}
	}
	else {
		std::cout << " tcp " << std::endl;
		tcp = true;
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
}

 Client::~Client()
{
}
