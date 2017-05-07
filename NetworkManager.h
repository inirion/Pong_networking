#pragma once
#include <memory>
#include "Config.h"

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
	#include <iphlpapi.h>
	#pragma comment(lib, "IPHLPAPI.lib")
#elif
	#include <sys/types.h>
	#include <ifaddrs.h>
#endif


class NetworkManager
{
private:
	std::shared_ptr<in_addr> getInterfacesUnix();
	std::shared_ptr<in_addr> getInterfacesWin();
public:
	NetworkManager();
	~NetworkManager();
	std::shared_ptr<in_addr> getInterfaces();
};

