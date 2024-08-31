#pragma once
#include <context.hpp>
#include <SFML/Graphics.hpp>
#include <pallet.hpp>
#include <sceneNode.hpp>
#include <helpers.hpp>

class Ship 
	: public SceneNode
{
public:
	typedef std::unique_ptr<Ship> Ptr;
	Ship(const Context& context);

	void updateCurrent(const sf::Time& dt);
	void processInput(const sf::Event& event);
	
	virtual void drawCurrent(sf::RenderTarget& window, sf::RenderStates states) const;

private:
	const Context &mContext;
	sf::VertexArray vertecies;
	sf::VertexArray tail;

	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f mVelocity;
	sf::Transform mTransform;
	sf::Vector2f mDirection;
	sf::Clock mClock;

	void removeChildren();
};
