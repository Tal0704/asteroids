#include <pallet.hpp>
#define SIZE 1

Pallet::Pallet(const vector2& position, Context context)
	: mContext(context)
	, mPallet(SIZE)
	, mTtl(sf::seconds(1.5))
	, mCreationTime(mContext.clock.getElapsedTime())
{
	initPallet(position);
}

Pallet::Pallet(float x, float y, Context context)
	: mContext(context)
	, mPallet(SIZE)
	, mTtl(sf::seconds(1.5))
{
	initPallet(sf::Vector2f(x, y));
}

void Pallet::initPallet(const sf::Vector2f& v)
{
	mPallet.setFillColor(sf::Color::White);
	mPallet.setPosition(v);
}

void Pallet::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mPallet, states);
}

void Pallet::setDirection(const sf::Vector2f& dir)
{
	mDirection = dir;
}

void Pallet::updateCurrent(const sf::Time& dt)
{
	mPallet.move(mDirection * mSpeed * dt.asSeconds());
	if(isDead())
	{
		isPendingRemoval = true;
	}
}

bool Pallet::isDead()
{
	return (mContext.clock.getElapsedTime() - mCreationTime) >= mTtl;
}
