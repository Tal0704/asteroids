#include <SFML/Window/Event.hpp>
#include <world.hpp>

#define SPEED 4
#define ANGLE 0.2

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mShip);
}

void World::handleEvent(const sf::Event& event)
{
}

void World::update(const sf::Time& dt)
{
	mShip.update(dt);
}
