#pragma once
#include <SFML/Network.hpp>
#include "Config.h"
#include <vector>
#include <string>
#include <tuple>
#include <chrono>

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

#define ConnectionText(btn) (std::get<TupleFields::NAME>(btn))
#define ConnectionIP(btn) (std::get<TupleFields::IPADRESS>(btn))

using serverTuple = std::tuple<sf::IpAddress, std::string, STATES, float>;
enum TupleFields { IPADRESS, NAME, STATE, TIMESTAMP};

class Broadcaster
{
private:

	unsigned short broadcastPort;
	float lastFrameTime;
	const std::string serverName;
	std::vector<serverTuple> conns;
	sf::UdpSocket s;	
	sf::Text list;
	bool checkNewConn();
	void printConns();

	serverTuple onNewConnection();
	void broadcast(STATES);
public:
	void update();
	void close();
	std::vector<serverTuple> getConns();
	Broadcaster(unsigned short broadcastPort, const std::string &serverName = "");
	~Broadcaster();
};

