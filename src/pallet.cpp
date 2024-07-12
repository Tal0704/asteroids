#include <pallet.hpp>
#define SIZE 1

Pallet::Pallet(const vector2& position)
	: mPallet(SIZE)
{
	mPallet.setFillColor(sf::Color::White);
	mPallet.setPosition(position);
}

Pallet::Pallet(float x, float y)
{
	Pallet(vector2(x, y));
}

void Pallet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mPallet, states);
}

void Pallet::setVelocity(const vector2& vel)
{
	mVel = vel;
}

vector2 Pallet::getVelocity()
{
	return mVel;
}

void Pallet::update(const sf::Time& dt)
{
	mPallet.move(mVel * dt.asSeconds());
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
