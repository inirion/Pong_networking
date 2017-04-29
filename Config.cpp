#include<SFML\Graphics.hpp>
#include "Config.h"

sf::Clock Config::clock;
sf::Clock Config::FPSclock;
float Config::dtime = 0.0f;

bool Config::inited = false;

void Config::init() {
	if (!inited) {
		inited = true;
	}
}