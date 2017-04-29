#pragma once
#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable
{
private:
	sf::Vector2f position;
	sf::RectangleShape paddle;
	sf::RenderWindow& rw;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() { return position; }

	Paddle(sf::RenderWindow& window, bool ai);
	inline sf::RectangleShape& getPaddle() { return paddle; }

	inline sf::FloatRect getPaddleRect() {
		return paddle.getGlobalBounds();
	}

	~Paddle();
	void movePaddle();
};

