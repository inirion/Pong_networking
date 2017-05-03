#pragma once
#include <SFML/Network.hpp>
#include "Networking.h"
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

using serverTuple = std::tuple<sf::IpAddress, std::string, STATES, double>;
enum TupleFields { IPADRESS, NAME, STATE, TIMESTAMP};

class Broadcaster : public Networking<sf::UdpSocket>
{
private:
	sf::Int32 lastFrameTime;
	const std::string serverName;
	sf::IpAddress incomingConnectionAddress;
	std::vector<serverTuple> conns;
	sf::Text list;
	bool checkNewConn();
	void printConns();

	serverTuple onNewConnection();
	void broadcast(STATES);
public:
	bool Send(sf::Packet)override;
	bool Recive() override;

	void update();
	void close();
	std::vector<serverTuple> getConns();
	Broadcaster(const std::string &serverName = "");
	~Broadcaster();
};

