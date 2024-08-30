#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <ship.hpp>

#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)

Ship::Ship(const Context& context)
	: mContext(context)
	, vertecies(sf::PrimitiveType::LineStrip, 6)
	, tail(sf::LineStrip, 3)
	, mDirection(0, -1)
	, mClock()
{
	vertecies[0].position = sf::Vector2f(-0.4f, -0.5f);
	vertecies[1].position = sf::Vector2f(0.0f, 0.5f);
	vertecies[2].position = sf::Vector2f(0.4f, -0.5f);
	vertecies[3].position = sf::Vector2f(0.3f, -0.4f);
	vertecies[4].position = sf::Vector2f(-0.3f, -0.4f);
	vertecies[5].position = sf::Vector2f(-0.4f, -0.5f);

	tail[0].position = sf::Vector2f(0.3f, -0.4f);
	tail[1].position = sf::Vector2f(0.0, -0.6);
	tail[2].position = sf::Vector2f(-0.3f, -0.4f);

	position = ORIGIN;
}

void Ship::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	static sf::Clock clock;
	static bool showTail = true;
	if(clock.getElapsedTime().asMilliseconds() % 200)
	{
		showTail = !showTail;
	}
	states.transform *= mTransform;

	target.draw(vertecies, states);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (showTail)
			target.draw(tail, states);
	}
}

void Ship::updateCurrent(const sf::Time& dt)
{
	#define SHIP_SPEED 3.f
	#define ROT_SPEED 5
	#define PALLET_SPEED 50.f
	#define DRAG 0.02
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Transform t;
		t.rotate(-ROT_SPEED);
		mDirection = t.transformPoint(mDirection);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Transform t;
		t.rotate(ROT_SPEED);
		mDirection = t.transformPoint(mDirection);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mVelocity += mDirection * SHIP_SPEED * dt.asSeconds();
	}

	constexpr float drag = (1.0 - DRAG);
	mVelocity = mVelocity * drag;
	position += (mVelocity);

	sf::Vector2u borders = mContext.window.getSize();

	if (position.x < 0)
		position.x = borders.x;
	if (position.y < 0)
		position.y = borders.y;
	
	if (position.x > borders.x)
		position.x = 0;
	if (position.y > borders.y)
		position.y = 0;
	mTransform = sf::Transform::Identity;
	mTransform.translate(position).scale(SCALE).rotate(angleFromVect(mDirection) - 90);
}

void Ship::processInput(const sf::Event& event)
{
	if (event.type == event.KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Space)
		{
			std::unique_ptr<Pallet> pallet = std::make_unique<Pallet>(mTransform.transformPoint(vertecies[1].position));
			pallet->setDirection(mDirection);
			attachChild(std::move(pallet));
		}
	}
}
