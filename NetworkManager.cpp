#include <iostream>

#include "NetworkManager.h"



std::shared_ptr<in_addr> NetworkManager::getInterfacesUnix()
{
	return std::shared_ptr<in_addr>();
}

std::shared_ptr<in_addr> NetworkManager::getInterfacesWin()
{
	return std::shared_ptr<in_addr>();
}

NetworkManager::NetworkManager()
{
#if PLATFORM == PLATFORM_WINDOWS
	std::cout << "Hello, Windows user!" << std::endl;
#elif 
	std::cout << "Hello, Unix user!" << std::endl;
#endif
}


NetworkManager::~NetworkManager()
{
}

std::shared_ptr<in_addr> NetworkManager::getInterfaces()
{
#if PLATFORM == PLATFORM_WINDOWS
	return getInterfacesWin();
#elif 
	return getInterfacesUnix();
#endif
}
