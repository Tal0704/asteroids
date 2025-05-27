#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <ship.hpp>
#include <asteroid.hpp>
#include <SFML/System/Angle.hpp>

#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)

void Ship::initVertecies() {
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

	using namespace sf::Literals;
	setPosition(ORIGIN);
	setRotation(180_deg);
	setScale(SCALE);
}

Ship::Ship(const Context& context, uint8_t lives)
	: mContext(context)
	, mVertecies(sf::PrimitiveType::LineStrip, 9)
	, mTail(sf::PrimitiveType::LineStrip, 3)
	, mNormal(0, -1)
	, mClock()
	, mLives(lives)
	, mPallets()
{
	initVertecies();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
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

	const sf::Angle angle = sf::Vector2f(mNormal * dt.asSeconds()).angle() - sf::degrees(90);
	setRotation(angle);

	constexpr float drag = (1.0 - DRAG);
	mVelocity = mVelocity * drag;
	move(mVelocity * dt.asSeconds());

	sf::Vector2u borders = mContext.window.getSize();
	if (getPosition().x < 0)
		setPosition(sf::Vector2f(borders.x, getPosition().y));
	if (getPosition().y < 0)
		setPosition(sf::Vector2f(getPosition().x, borders.y));
	
	if (getPosition().x > borders.x)
		setPosition(sf::Vector2f(0, getPosition().y));
	if (getPosition().y > borders.y)
		setPosition(sf::Vector2f(getPosition().x, 0));

}

void Ship::processInput(const std::optional<sf::Event>& event)
{
	if (event->is<sf::Event::KeyPressed>())
	{
		if(event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		sf::Transform t;
		t.rotate(sf::degrees(-ROT_SPEED));
		mNormal = t.transformPoint(mNormal);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sf::Transform t;
		t.rotate(sf::degrees(ROT_SPEED));
		mNormal = t.transformPoint(mNormal);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
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
	return asteroid.status == Asteroid::Status::Alive && (distance(asteroid.getPosition(), getPosition()) - 10 <= (asteroid.getRadius() * SCALE).length());
}

bool Ship::collidePallet(const Pallet& pallet) const
{
	sf::FloatRect bounds = getGlobalBounds();
	float value = 10.f;
	bounds.size.x -= value;
	bounds.size.y -= value;
	return bounds.contains(pallet.getPosition());
}

bool Ship::isDead() const {
	return mLives == 0;
}
void Ship::destroy() {
	mLives--;
	initVertecies();
}
