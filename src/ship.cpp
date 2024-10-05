#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <ship.hpp>

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
	#define ROT_SPEED 5
	#define PALLET_SPEED 50.f
	#define DRAG 0.02
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Transform t;
		t.rotate(-ROT_SPEED);
		mNormal = t.transformPoint(mNormal);
		setRotation(angleFromVect(mNormal) - 90.f);

	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Transform t;
		t.rotate(ROT_SPEED);
		mNormal = t.transformPoint(mNormal);
		setRotation(angleFromVect(mNormal) - 90.f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mVelocity += mNormal * SHIP_SPEED * dt.asSeconds();
	}

	constexpr float drag = (1.0 - DRAG);
	mVelocity = mVelocity * drag;
	move(mVelocity);

	sf::Vector2u borders = mContext.window.getSize();

	if (getPosition().x < 0)
		setPosition(borders.x, getPosition().y);
	if (getPosition().y < 0)
		setPosition(getPosition().x, borders.y);
	
	if (getPosition().x > borders.x)
		setPosition(0, getPosition().y);
	if (getPosition().y > borders.y)
		setPosition(getPosition().x, 0);

	setScale(SCALE, SCALE);
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
			mPallets.emplace_back(std::move(pallet));
		}
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

