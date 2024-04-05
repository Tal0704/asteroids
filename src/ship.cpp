#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <ship.hpp>

#define PI 3.14159265
#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)

std::ostream& operator<<(std::ostream& stream, const vector2 v)
{
	stream << v.x << ", " << v.y;

	return stream;
}

vector2 velocityFromSpeed(float speed, float angle)
{
	sf::Vector2f direction;
	direction.x = speed * std::cos(angle * PI / 180 + 0.5 * PI);
	direction.y = speed * std::sin(angle * PI / 180 + 0.5 * PI);

	return direction;
}

Ship::Ship(const sf::Vector2f& borders)
	: vertecies(sf::PrimitiveType::LineStrip, 6)
	, tail(sf::LineStrip, 3)
	, borders(borders)
{
	vertecies[0].position = sf::Vector2f(-0.4f, -0.5f);
	vertecies[1].position = sf::Vector2f(0.0f, 0.5f);
	vertecies[2].position = sf::Vector2f(0.4f, -0.5f);
	vertecies[3].position = sf::Vector2f(0.3f, -0.4f);
	vertecies[4].position = sf::Vector2f(-0.3f, -0.4f);
	vertecies[5].position = sf::Vector2f(-0.4f, -0.5f);

	tail[0].position = sf::Vector2f(0.3f, -0.4f);
	tail[1].position = sf::Vector2f(0.0, -0.6);
	tail[2].position = sf::Vector2f(-0.3f, -0.4f);

	position = ORIGIN;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	static sf::Clock clock;
	static bool showTail = true;
	if(clock.getElapsedTime().asMilliseconds() % 200)
	{
		showTail = !showTail;
	}
	states.transform.translate(position).scale(SCALE).rotate(rotation);

	target.draw(vertecies, states);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (showTail)
			target.draw(tail, states);
	}
	for (const auto& pallet: mPallets)
		target.draw(*pallet);
}

void Ship::update(const sf::Time& dt)
{
	#define SHIP_SPEED 3.f
	#define ROT_SPEED 500
	#define PALLET_SPEED 12.f
	#define DRAG 0.02
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotation -= dt.asSeconds() * ROT_SPEED;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotation += dt.asSeconds() * ROT_SPEED;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity = velocity + (velocityFromSpeed(SHIP_SPEED, rotation) * dt.asSeconds() * SHIP_SPEED);
	}

// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	{
//		auto pallet = std::make_unique<Pallet>(0.0f, 0.5f);
//		
//		pallet->setVelocity(velocityFromSpeed(PALLET_SPEED, rotation));
//		std::cout << pallet->getPosition() << "\n";
//		mPallets.push_back(std::move(pallet));
//	}

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
	for(const auto& pallet: mPallets)
	{
		pallet->update(dt);
	}
}
