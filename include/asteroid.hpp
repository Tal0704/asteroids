#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <sceneNode.hpp>

class Asteroid
	: public SceneNode
{
public:
	typedef std::unique_ptr<Asteroid> Ptr;
	Asteroid();

	sf::Vector2f position;
	sf::Vector2f velocity;

	void update(const sf::Time& dt);

private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray mVertecies;
};
