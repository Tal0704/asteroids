#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <ship.hpp>

class World
	: public sf::Drawable
{
public:
	Ship ship;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
