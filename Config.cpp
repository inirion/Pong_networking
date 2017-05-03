#include<SFML/Graphics.hpp>
#include "Config.h"

sf::Clock Config::clock;
sf::Clock Config::FPSclock;
float Config::dtime = 0.0f;
bool Config::isServer = false;
bool Config::inited = false;
bool Config::isPongPlaying = false;
bool Config::TCPstart = false;
unsigned short Config::port = 50001;

void Config::init() {
	if (!inited) {
		inited = true;
	}
}