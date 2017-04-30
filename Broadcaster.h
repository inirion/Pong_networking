#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <string>

using serverPair = std::pair<sf::IpAddress, std::string>;

class Broadcaster
{
private:
	unsigned short broadcastPort;
	const std::string serverName;
	std::vector<serverPair> conns;
	sf::UdpSocket s;
public:
	Broadcaster(unsigned short broadcastPort, const std::string &serverName = "");
	serverPair onNewConnection();
	std::vector<serverPair> & getAllConnections();
	void broadcast();
	~Broadcaster();
};

