#pragma once
#include <context.hpp>
#include <SFML/Graphics.hpp>
#include <pallet.hpp>
#include <helpers.hpp>
#include <cassert>

class Ship 
	: public sf::Shape
{
public:
	typedef std::unique_ptr<Ship> Ptr;
	Ship(const Context& context);

	void update(const sf::Time& dt);
	void processInput(const sf::Event& event);

	virtual std::size_t getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;
	
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

	const std::vector<Pallet::Ptr>& getPallets();

private:
	const Context &mContext;
	sf::VertexArray mVertecies;
	sf::VertexArray mTail;

	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f mVelocity;
	sf::Transform mTransform;
	sf::Vector2f mDirection;
	sf::Clock mClock;

	std::vector<Pallet::Ptr> mPallets;
};
