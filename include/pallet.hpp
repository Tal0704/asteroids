#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <helpers.hpp>
#include <context.hpp>

typedef sf::Vector2f vector2;

class Pallet
	: public sf::CircleShape
{
public:
	typedef std::unique_ptr<Pallet> Ptr;

	Pallet(const vector2& position, Context context);
	Pallet(float x, float y, Context context);
                          
	void setDirection(const vector2& dir);
	void update(const sf::Time& dt);

	bool isPendingRemoveal() const;

	float getRadius() const;

private:
	Context mContext;
	vector2 mDirection;
	static constexpr float mSpeed = 50.f;

	sf::Time mTtl;
	sf::Time mCreationTime;
};
