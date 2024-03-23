#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Window/Event.hpp>
#include <ship.hpp>

class World
	: public sf::Drawable
{
public:
	Ship mShip;

	void handleEvent(const sf::Event& event);
	
	void update(const sf::Time& dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
