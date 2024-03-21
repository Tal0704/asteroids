#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class Ship
	: public sf::Drawable
	, public sf::Transformable
{
public:
	Ship();

private:
	sf::VertexArray mShip;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
