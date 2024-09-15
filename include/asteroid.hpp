#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <context.hpp>

class Asteroid
	: public sf::Shape
{
public:
	typedef std::unique_ptr<Asteroid> Ptr;
	Asteroid(const Context& context);

	sf::Vector2f position;
	sf::Vector2f velocity;

	virtual std::size_t getPointCount() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;

	void update(const sf::Time& dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray mVertecies;

	Context mContext;
};
