#include <ship.hpp>

#define PI 3.14159265
#define DRAG 0.03;
#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)
#define ANGLE 3 * 180 / PI

Ship::Ship()
	: vertecies(sf::PrimitiveType::LineStrip, 6)
{
	vertecies[0].position = sf::Vector2f(-0.4f, -0.5f);
	vertecies[1].position = sf::Vector2f(0.0f, 0.5f);
	vertecies[2].position = sf::Vector2f(0.4f, -0.5f);
	vertecies[3].position = sf::Vector2f(0.3f, -0.4f);
	vertecies[4].position = sf::Vector2f(-0.3f, -0.4f);
	vertecies[5].position = sf::Vector2f(-0.4f, -0.5f);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(ORIGIN + position).scale(SCALE).rotate(rotation);

	target.draw(vertecies, states);
}
