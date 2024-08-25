#pragma once
#include <context.hpp>
#include <SFML/Graphics.hpp>
#include <pallet.hpp>
#include <sceneNode.hpp>

class Ship 
	: public SceneNode
{
public:
	typedef std::unique_ptr<Ship> Ptr;
	Ship(const Context& context);

	void update(const sf::Time& dt);
	void processInput(const sf::Event& event);
	
	virtual void drawCurrent(sf::RenderTarget& window, sf::RenderStates states) const;

private:
	const Context &mContext;
	sf::VertexArray vertecies;
	sf::VertexArray tail;

	sf::Transform transform;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Transform mTransform;
	float rotation;
	std::vector<Pallet::Ptr> mPallets;
	sf::Clock mClock;
};
