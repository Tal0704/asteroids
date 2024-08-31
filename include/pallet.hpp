#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <sceneNode.hpp>
#include <helpers.hpp>
#include <context.hpp>

typedef sf::Vector2f vector2;

class Pallet
	: public SceneNode
{
public:
	typedef std::unique_ptr<Pallet> Ptr;

	Pallet(const vector2& position, Context context);
	Pallet(float x, float y, Context context);
                          
	void setDirection(const vector2& dir);
	void updateCurrent(const sf::Time& dt);

	bool isDead();

private:
	Context mContext;
	vector2 mDirection;
	static constexpr float mSpeed = 50.f;

	sf::CircleShape mPallet;
	sf::Time mTtl;
	sf::Time mCreationTime;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void initPallet(const sf::Vector2f& v);
};
