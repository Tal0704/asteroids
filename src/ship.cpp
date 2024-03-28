#include <cmath>
#include <ship.hpp>

#define PI 3.14159265
#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)

Ship::Ship(const sf::Vector2f& borders)
	: vertecies(sf::PrimitiveType::LineStrip, 6)
	, borders(borders)
{
	vertecies[0].position = sf::Vector2f(-0.4f, -0.5f);
	vertecies[1].position = sf::Vector2f(0.0f, 0.5f);
	vertecies[2].position = sf::Vector2f(0.4f, -0.5f);
	vertecies[3].position = sf::Vector2f(0.3f, -0.4f);
	vertecies[4].position = sf::Vector2f(-0.3f, -0.4f);
	vertecies[5].position = sf::Vector2f(-0.4f, -0.5f);

	position = ORIGIN;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(position).scale(SCALE).rotate(rotation);

	target.draw(vertecies, states);
}

void Ship::update(const sf::Time& dt)
{
	#define SHIP_SPEED 10.f
	#define ROT_SPEED 600
	#define DRAG 0.02
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotation -= dt.asSeconds() * ROT_SPEED;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotation += dt.asSeconds() * ROT_SPEED;
	}

	sf::Vector2f direction;
	direction.x = std::cos(rotation * PI / 180 + 0.5 * PI);
	direction.y = std::sin(rotation * PI / 180 + 0.5 * PI);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity = velocity + (direction * dt.asSeconds() * SHIP_SPEED);
	}

	velocity.x *= 1.0 - DRAG;
	velocity.y *= 1.0 - DRAG;
	position += velocity;

	if (position.x < 0)
		position.x = borders.x;
	if (position.y < 0)
		position.y = borders.y;
	
	if (position.x > borders.x)
		position.x = 0;
	if (position.y > borders.y)
		position.y = 0;
}
