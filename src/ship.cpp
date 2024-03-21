#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"
#include <ship.hpp>

#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(50.f, 50.f)

Ship::Ship()
	: mShip(sf::PrimitiveType::LineStrip, 6)
{
	mShip[0].position = sf::Vector2f(-0.4f, -0.5f);
	mShip[1].position = sf::Vector2f(0.0f, 0.5f);
	mShip[2].position = sf::Vector2f(0.4f, -0.5f);
	mShip[3].position = sf::Vector2f(0.3f, -0.4f);
	mShip[4].position = sf::Vector2f(-0.3f, -0.4f);
	mShip[5].position = sf::Vector2f(-0.4f, -0.5f);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(ORIGIN).scale(SCALE) *= getTransform();

	target.draw(mShip, states);
}
