#include <world.hpp>

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ship);
}
