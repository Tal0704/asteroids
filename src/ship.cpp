#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <ship.hpp>
#include <asteroid.hpp>

#define SCALE 30.0f
#define ORIGIN sf::Vector2f(150.f, 150.f)

Ship::Ship(const Context& context)
	: mContext(context)
	, mVertecies(sf::PrimitiveType::LineStrip, 9)
	, mTail(sf::LineStrip, 3)
	, mNormal(0, -1)
	, mClock()
	, mPallets()
{
	mVertecies[0].position = sf::Vector2f(-0.4f, -0.5f);
	mVertecies[1].position = sf::Vector2f(0.0f, 0.5f);
	mVertecies[2].position = sf::Vector2f(0.4f, -0.5f);
	mVertecies[3].position = sf::Vector2f(0.3f, -0.4f);
	mVertecies[4].position = sf::Vector2f(-0.3f, -0.4f);
	mVertecies[5].position = sf::Vector2f(-0.4f, -0.5f);

	// tail
	mVertecies[6].position = sf::Vector2f(0.3f, -0.4f);
	mVertecies[7].position = sf::Vector2f(0.0, -0.6);
	mVertecies[8].position = sf::Vector2f(-0.3f, -0.4f);
	sf::Shape::update();

	setPosition(ORIGIN);
	setRotation(180);
	setScale(SCALE, SCALE);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	static sf::Clock clock;
	static bool showTail = true;
	if(clock.getElapsedTime().asMilliseconds() % 200)
	{
		showTail = !showTail;
	}
	states.transform *= getTransform();

	target.draw(mVertecies, states);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (showTail)
			target.draw(mTail, states);
	}

	for(auto& pallet: mPallets)
	{
		target.draw(*pallet);
	}
}

void Ship::update(const sf::Time& dt)
{
	#define SHIP_SPEED 3.f
	#define ROT_SPEED 3
	#define PALLET_SPEED 50.f
	#define DRAG 0.02

	setRotation(angleFromVect(mNormal * dt.asSeconds()) - 90.f);

	constexpr float drag = (1.0 - DRAG);
	mVelocity = mVelocity * drag;
	move(mVelocity * dt.asSeconds());

	sf::Vector2u borders = mContext.window.getSize();
	if (getPosition().x < 0)
		setPosition(borders.x, getPosition().y);
	if (getPosition().y < 0)
		setPosition(getPosition().x, borders.y);
	
	if (getPosition().x > borders.x)
		setPosition(0, getPosition().y);
	if (getPosition().y > borders.y)
		setPosition(getPosition().x, 0);

}

void Ship::processInput(const sf::Event& event)
{
	if (event.type == event.KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Space)
		{
			std::unique_ptr<Pallet> pallet = std::make_unique<Pallet>(
					getTransform().transformPoint(mVertecies[1].position), mContext);
			pallet->setDirection(mNormal);
			pallet->move(mNormal * 4.f);
			mPallets.emplace_back(std::move(pallet));
		}
	}
}

void Ship::processRealTime()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Transform t;
		t.rotate(-ROT_SPEED);
		mNormal = t.transformPoint(mNormal);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Transform t;
		t.rotate(ROT_SPEED);
		mNormal = t.transformPoint(mNormal);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mVelocity += mNormal * SHIP_SPEED;
	}
}


std::size_t Ship::getPointCount() const
{
	return mVertecies.getVertexCount();
}

sf::Vector2f Ship::getPoint(std::size_t index) const
{
	assert(index < getPointCount());
	return mVertecies[index].position;
}

const std::vector<Pallet::Ptr>& Ship::getPallets()
{
	return mPallets;
}

bool Ship::collideAsteroid(const Asteroid& asteroid) const
{
	return distance(asteroid.getPosition(), getPosition()) - 10 <= (asteroid.getRadius() * SCALE);
}

bool Ship::collidePallet(const Pallet& pallet) const
{
	sf::FloatRect bounds = getGlobalBounds();
	float value = 6.f;
	bounds.top += value;
	bounds.left += value;
	bounds.width -= value;
	bounds.height -= value;
	return bounds.contains(pallet.getPosition());
}
