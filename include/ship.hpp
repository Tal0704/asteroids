#pragma once
#include "SFML/Graphics/Transformable.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

class Ship
	: public sf::Drawable
	, public sf::Transformable
{
public:
	Ship();

	void setSpeed(float speed);
	void update(const sf::Time& dt);

	void handleRealTime(const sf::Time dt);

private:
	sf::VertexArray mShip;
	float mSpeed;
	float mAngle;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
