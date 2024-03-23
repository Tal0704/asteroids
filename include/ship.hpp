#pragma once
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

struct Ship 
	: public sf::Drawable
{
	Ship();
	sf::VertexArray vertecies;

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float rotation;
};
