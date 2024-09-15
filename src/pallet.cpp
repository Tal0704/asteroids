#include <pallet.hpp>

Pallet::Pallet(const vector2& position, Context context)
	: mContext(context)
	, mTtl(sf::seconds(1.5))
	, mCreationTime(mContext.clock.getElapsedTime())
{
	sf::Shape::update();
	// initPallet(position);
}

Pallet::Pallet(float x, float y, Context context)
	: mContext(context)
	, mTtl(sf::seconds(1.5))
{
	sf::Shape::update();
	/* initPallet(sf::Vector2f(x, y)); */
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

const sf::Vector2f& Pallet::getRadius() const { return mRadius; }

std::size_t Pallet::getPointCount() const { return 1; }

sf::Vector2f Pallet::getPoint(std::size_t index) const
{
	return this->getPosition();
}
