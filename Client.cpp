#include "Client.h"
#include "Config.h"
bool Client::setConnection(sf::IpAddress ip)
{
	this->ip = ip;

	if (socket.connect(ip, port) != sf::Socket::Done) return false;
	else return true;

}
bool Client::Send(sf::Packet packet)
{
	if (socket.send(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

bool Client::Recive()
{
	if (socket.receive(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

 Client::Client():Networking(Config::port)
{

	socket.setBlocking(false);

}

 Client::~Client()
{
	 
}
