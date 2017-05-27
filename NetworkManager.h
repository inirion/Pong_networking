#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>

#include "Config.h"

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <iphlpapi.h>

	#pragma comment(lib, "iphlpapi.lib")
	#pragma comment(lib, "ws2_32.lib")
#elif
	#define _GNU_SOURCE 
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <ifaddrs.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <linux/if_link.h>
#endif

using AddressTuple = std::tuple<sf::IpAddress, sf::IpAddress, sf::IpAddress, sf::IpAddress>;
using AddressVectorPtr = std::shared_ptr<std::vector<AddressTuple>>;
enum AddressTupleFields { ASSIGNED_IP, NET, SUBNET, BROADCAST };

class NetworkManager
{
private:
	AddressVectorPtr getInterfacesUnix();
	AddressVectorPtr getInterfacesWin();
	AddressTuple makeTupleWin(const std::string &host, const std::string &mask);
	AddressTuple makeTupleUnix(const std::string &host, const std::string &mask);
public:
	NetworkManager();
	~NetworkManager();
	AddressVectorPtr getInterfaces();
};

