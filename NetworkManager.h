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
	#include <sys/types.h>
	#include <ifaddrs.h>
#endif

using AddressTuple = std::tuple<sf::IpAddress, sf::IpAddress, sf::IpAddress, sf::IpAddress>;
using AddressVectorPtr = std::shared_ptr<std::vector<AddressTuple>>;
enum AddressTupleFields { ASSIGNED_IP, NET, SUBNET, BROADCAST };

class NetworkManager
{
private:
	AddressVectorPtr getInterfacesUnix();
	AddressVectorPtr getInterfacesWin();
	AddressTuple makeTuple(const std::string &host, const std::string &mask);
public:
	NetworkManager();
	~NetworkManager();
	AddressVectorPtr getInterfaces();
};

