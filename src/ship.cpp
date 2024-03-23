#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>
#include <ship.hpp>

#define PI 3.14159265
#define DRAG 0.03;
#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)
#define ANGLE 3 * 180 / PI

Ship::Ship()
	: mShip(sf::PrimitiveType::LineStrip, 6), mSpeed(0), mAngle(0)
{
	mShip[0].position = sf::Vector2f(-0.4f, -0.5f);
	mShip[1].position = sf::Vector2f(0.0f, 0.5f);
	mShip[2].position = sf::Vector2f(0.4f, -0.5f);
	mShip[3].position = sf::Vector2f(0.3f, -0.4f);
	mShip[4].position = sf::Vector2f(-0.3f, -0.4f);
	mShip[5].position = sf::Vector2f(-0.4f, -0.5f);
}

void Ship::setSpeed(float speed)
{
	mSpeed = speed;
}

void Ship::update(const sf::Time& dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setSpeed(5);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotate(-ANGLE * dt.asSeconds());
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotate(ANGLE * dt.asSeconds());
	}

	sf::Vector2f vel;
	vel.x = mSpeed * std::cos(getRotation() / dt.asSeconds() + PI / 2);
	vel.y = mSpeed * std::sin(getRotation() / dt.asSeconds() + PI / 2);
	move(vel * dt.asSeconds());
	mSpeed *= 1.0 - DRAG;
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(ORIGIN).scale(SCALE) *= getTransform();;

	target.draw(mShip, states);
}
