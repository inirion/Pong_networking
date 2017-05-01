#pragma once
#include <SFML/Network.hpp>
#include "Config.h"
#include <vector>
#include <string>
#include <tuple>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

enum class STATES {
	BROADCASTING = 0,
	EXIT = 1,
	FAILED = 2
};


using serverTuple = std::tuple<sf::IpAddress, std::string, STATES>;
enum TupleFields { IPADRESS, NAME, STATE };

class Broadcaster
{
private:

	unsigned short broadcastPort;
	const std::string serverName;
	std::vector<serverTuple> conns;
	sf::UdpSocket s;	
	
	sf::Text servers;

	bool checkNewConn();
	void printConns();


	serverTuple onNewConnection();
	void broadcast(STATES);
public:
	void update();
	Broadcaster(unsigned short broadcastPort, const std::string &serverName = "");
	~Broadcaster();
};

