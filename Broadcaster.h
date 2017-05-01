#pragma once
#include <SFML/Network.hpp>
#include "Config.h"
#include <vector>
#include <string>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using serverPair = std::pair<sf::IpAddress, std::string>;

enum class STATES {
	BROADCASTING = 0,
	EXIT = 1
};

class Broadcaster
{
private:

	unsigned short broadcastPort;
	const std::string serverName;
	std::vector<serverPair> conns;
	sf::UdpSocket s;	
	
	sf::Text servers;

	bool checkNewConn();
	void printConns();


	serverPair onNewConnection();
	void broadcast(STATES);
public:
	void update();
	Broadcaster(unsigned short broadcastPort, const std::string &serverName = "");
	~Broadcaster();
};

