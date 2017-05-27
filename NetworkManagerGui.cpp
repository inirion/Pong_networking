#include "NetworkManagerGui.h"

NetworkManagerGui::NetworkManagerGui(sf::RenderWindow& rw) : rw(rw)
{

}


void NetworkManagerGui::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void NetworkManagerGui::update(sf::Event e)
{
	AddressVectorPtr availableInterfaces = nm.getInterfaces();
}

NetworkManagerGui::~NetworkManagerGui()
{
}
