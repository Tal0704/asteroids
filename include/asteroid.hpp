#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <context.hpp>

class Ship;

class Asteroid
	: public sf::Shape
{
public:
	enum Status{
		Alive,
		Particles,
		Dead
	};
	typedef std::unique_ptr<Asteroid> Ptr;
	Asteroid(const Context& context);

	virtual std::size_t getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;

	void update(const sf::Time& dt);
	void kill();
	bool isFinishedExplosion() const;

	float getRadius() const;
	Status status;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray mVertecies;

	sf::Clock mTtlAfterShoot;
	float mRadius;
	std::vector<sf::Vector2f> mVelocities;
	Context mContext;
};
