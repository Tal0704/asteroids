#include <pallet.hpp>
#include <asteroid.hpp>

#define SCALE 30.f

Pallet::Pallet(const vector2& position, Context context)
	: sf::CircleShape(1)
	, mContext(context)
	, mTtl(sf::seconds(1.5))
	, mCreationTime(mContext.clock.getElapsedTime())
{
	setPosition(position);
	sf::Shape::update();
}

Pallet::Pallet(float x, float y, Context context)
	: mContext(context)
	, mTtl(sf::seconds(1.5))
{
	this->setPosition(x, y);
	sf::Shape::update();
}

void Pallet::setDirection(const sf::Vector2f& dir)
{
	mDirection = dir;
}

void Pallet::update(const sf::Time& dt)
{
	this->move(mDirection * mSpeed * dt.asSeconds());
}

bool Pallet::isPendingRemoveal() const
{
	return (mContext.clock.getElapsedTime() - mCreationTime) >= mTtl;
}

bool Pallet::collideAsteroid(const Asteroid& asteroid)
{
	return distance(asteroid.getPosition(), getPosition()) - 1 <= (asteroid.getRadius() * SCALE);
}
