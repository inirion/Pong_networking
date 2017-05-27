#pragma once
#include <SFML/Graphics.hpp>

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__unix__)
	#define PLATFORM PLATFORM_UNIX
#endif

class Config {

public:
	static bool TCPstart;
	static sf::Clock clock;
	static sf::Clock FPSclock;
	static float dtime;
	static bool isServer;
	static bool isPongPlaying;
	static bool inited;
	static void init();
	static unsigned short port;

};

#define CLOCKASSEC Config::clock.getElapsedTime().asSeconds()
#define CLOCKASMS Config::clock.getElapsedTime().asMilliseconds()
