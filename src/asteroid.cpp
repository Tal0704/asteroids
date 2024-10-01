#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include <ship.hpp>
#include <asteroid.hpp>
#include <random>

#define PI 3.14159265
#define ASTEROID_SPEED 2.0f
#define SCALE sf::Vector2f(30.0f, 30.f)

Asteroid::Asteroid(const Context& context)
	:mVertecies(sf::PrimitiveType::LineStrip)
	, mContext(context)
{
	float radius;

	std::random_device r;
	std::default_random_engine e(r());

	std::uniform_int_distribution<size_t> uniformIntDist(8, 10);
	mVertecies.resize(uniformIntDist(e));

	std::uniform_real_distribution<float> uniformFloatDist(0.4, 0.8);

	for(size_t i = 0; i < mVertecies.getVertexCount(); i++)
	{
		radius = uniformFloatDist(e);
		float angle = 2 * PI / mVertecies.getVertexCount();
		angle *= i;
		mVertecies[i].position = sf::Vector2f(radius * std::cos(angle), std::sin(angle) * radius);
	}
	mVertecies.append(mVertecies[0]);

	uniformFloatDist = std::uniform_real_distribution<float>(-10.f, 10.f);
	velocity.x = uniformFloatDist(e);
	velocity.y = uniformFloatDist(e);
	
	uniformIntDist = std::uniform_int_distribution<size_t>(100, 400);
	
	position.x = uniformIntDist(e);
	position.y = uniformIntDist(e);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(position).scale(SCALE);

	target.draw(mVertecies, states);
}

void Asteroid::update(const sf::Time& dt)
{
	position += velocity * dt.asSeconds() * ASTEROID_SPEED;
}


std::size_t Asteroid::getPointCount() const
{
	return mVertecies.getVertexCount();
}

sf::Vector2f Asteroid::getPoint(std::size_t index) const
{
	return mVertecies[index].position;
}

bool Asteroid::collideShip(const Ship& ship)
{
	return mVertecies.getBounds().intersects(ship.getBounds());
}
