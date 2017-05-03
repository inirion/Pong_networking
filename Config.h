#pragma once
#include <SFML\Graphics.hpp>

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
