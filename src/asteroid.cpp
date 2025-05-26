#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include <ship.hpp>
#include <asteroid.hpp>
#include <random>

#define PI 3.14159265
#define ASTEROID_SPEED 2.0f
#define SCALE 30.f

Asteroid::Asteroid(const Context& context)
	: status (Alive)
	, mVertecies(sf::PrimitiveType::LineStrip)
	, mVelocities(1)
	, mContext(context)
	
{
	mTtlAfterShoot.reset();
	std::random_device r;
	std::default_random_engine e(r());

	std::uniform_int_distribution<size_t> uniformIntDist(8, 10);
	mVertecies.resize(uniformIntDist(e));

	std::uniform_real_distribution<float> uniformFloatDist(0.4, 0.8);

	for(size_t i = 0; i < mVertecies.getVertexCount(); i++)
	{
		mRadius = uniformFloatDist(e);
		float angle = 2 * PI / mVertecies.getVertexCount();
		angle *= i;
		mVertecies[i].position = sf::Vector2f(mRadius * std::cos(angle), std::sin(angle) * mRadius);
	}
	mVertecies.append(mVertecies[0]);

	uniformFloatDist = std::uniform_real_distribution<float>(-10.f, 10.f);
	mVelocities[0].x = uniformFloatDist(e);
	mVelocities[0].y = uniformFloatDist(e);
	
	uniformIntDist = std::uniform_int_distribution<size_t>(100, 400);
	
	setPosition(sf::Vector2f(uniformIntDist(e), uniformIntDist(e)));
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (status == Alive){
		states.transform *= getTransform();
		states.transform.scale(sf::Vector2f(SCALE, SCALE));
	}
	
	target.draw(mVertecies, states);
}

void Asteroid::update(const sf::Time& dt)
{
	if(status == Alive) {
		move(mVelocities[0] * dt.asSeconds() * ASTEROID_SPEED);
	} else if(status == Particles) {
		for(uint i = 0; i < mVelocities.size(); i++) {
			mVertecies[i].position = mVertecies[i].position + mVelocities[i] * dt.asSeconds() * ASTEROID_SPEED;
		}
	}
}

std::size_t Asteroid::getPointCount() const
{
	return mVertecies.getVertexCount();
}

sf::Vector2f Asteroid::getPoint(std::size_t index) const
{
	return mVertecies[index].position;
}

float Asteroid::getRadius() const
{
	return mRadius;
}

void Asteroid::kill() {
	status = Particles;
	mVelocities.reserve(15);
	mVelocities.clear();
	mVertecies.resize(15);

	std::random_device r;
	std::default_random_engine e(r());

	std::uniform_real_distribution<float> uniformFloatDist(20, 40);

	mVertecies.setPrimitiveType(sf::PrimitiveType::Points);
	for(size_t i = 0; i < mVertecies.getVertexCount(); i++)
	{
		mVelocities.emplace_back(sf::Vector2f(uniformFloatDist(e), uniformFloatDist(e)));
		mVertecies[i].position = getPosition();
		mVertecies[i].color = sf::Color::White;
	}

	mTtlAfterShoot.start();
}

bool Asteroid::isFinishedExplosion() const {
	return (mTtlAfterShoot.getElapsedTime() >= sf::seconds(0.5)) && (status == Particles);
}
