#pragma once
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Ship 
	: public sf::Drawable
{
public:
	typedef std::unique_ptr<Ship> Ptr;
	Ship(const sf::Vector2f& borders);
	sf::VertexArray vertecies;

	void update(const sf::Time& dt);

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	sf::Vector2f borders;
	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float rotation;
};
