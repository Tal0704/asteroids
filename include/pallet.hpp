#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <sceneNode.hpp>

typedef sf::Vector2f vector2;

class Pallet
	: public SceneNode
{
public:
	typedef std::unique_ptr<Pallet> Ptr;

	Pallet(const vector2& position);
	Pallet(float x, float y);
	void setPosition(const vector2& position);
	void setPosition(float x, float y);
	vector2 getPosition();
                          
	void setVelocity(const vector2& velocity);
	vector2 getVelocity();
	void update(const sf::Time& dt);

private:
	vector2 mPos;
	vector2 mVel;

	sf::CircleShape mPallet;
	sf::Time mTtl;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};
