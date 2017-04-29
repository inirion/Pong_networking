#pragma once
#include <SFML\Graphics.hpp>

class Ball
{
private:
	sf::RenderWindow &rw;
	sf::Vector2f position;
	sf::CircleShape ball;
	sf::Vector2f movingCoords;
	float speed;
public:
	inline void move(sf::Vector2f val, float mul = 1.0f) { position += val*mul; }
	inline void reset(sf::Vector2f pos) { setPosition(pos); speed = 5.f; movingCoords = sf::Vector2f(-1, 0); }

	inline sf::Vector2f getMovingCoords() { return movingCoords; }
	inline void setMovingCoords(sf::Vector2f coords) { movingCoords = coords; speed += 0.3; }

	inline sf::CircleShape getBall() { return ball; }
	inline sf::FloatRect getBallRect() { return ball.getGlobalBounds(); }

	inline float getSpeed() { return speed; }

	inline sf::Vector2f getPosition() { return position; }
	inline void setPosition(sf::Vector2f pos) { this->position = pos; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
	Ball(sf::RenderWindow& window);
	~Ball();
};

