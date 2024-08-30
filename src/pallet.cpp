#include <pallet.hpp>
#define SIZE 1

Pallet::Pallet(const vector2& position)
	: mPallet(SIZE)
	, mTtl(sf::seconds(1.5))
{
	mPallet.setFillColor(sf::Color::White);
	mPallet.setPosition(position);
}

Pallet::Pallet(float x, float y)
{
	Pallet(vector2(x, y));
}

void Pallet::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mPallet, states);
}

void Pallet::setDirection(const sf::Vector2f& dir)
{
	mDirection = dir;
}

void Pallet::updateCurrent(const sf::Time& dt)
{
	mPallet.move(mDirection * mSpeed * dt.asSeconds());
}


void Pallet::setPosition(const vector2& pos)
{
	mPallet.setPosition(pos);
}

void Pallet::setPosition(float x, float y)
{
	setPosition(vector2(x, y));
}

vector2 Pallet::getPosition()
{
	return mPallet.getPosition();
}
