#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <context.hpp>

class Ship;

class Asteroid
	: public sf::Shape
{
public:
	typedef std::unique_ptr<Asteroid> Ptr;
	Asteroid(const Context& context);

	virtual std::size_t getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;

	void update(const sf::Time& dt);

	float getRadius() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray mVertecies;

	float mRadius;
	sf::Vector2f mVelocity;
	Context mContext;
};
