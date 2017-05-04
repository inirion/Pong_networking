#include "Server.h"

bool Server::setConnection()
{
	if (listener.accept(socket) != sf::Socket::Done) return false;
	else return true;
}

bool Server::Send(sf::Packet packet)
{
	if(socket.send(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

bool Server::Recive()
{
	if (socket.receive(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

Server::Server():Networking(Config::port)
{
	listener.setBlocking(false);
	socket.setBlocking(false);
	if (listener.listen(port) != sf::Socket::Done)
	{
		throw "Couldn't connect socket =(";
	}
}


Server::~Server()
{
}
