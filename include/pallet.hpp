#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <helpers.hpp>
#include <context.hpp>

typedef sf::Vector2f vector2;

class Pallet
	: public sf::Shape
{
public:
	typedef std::unique_ptr<Pallet> Ptr;

	Pallet(const vector2& position, Context context);
	Pallet(float x, float y, Context context);
                          
	void setDirection(const vector2& dir);
	void update(const sf::Time& dt);

	bool isPendingRemoveal() const;

	const sf::Vector2f& getRadius() const;
	virtual sf::Vector2f getPoint(std::size_t index) const;
	virtual std::size_t getPointCount() const;

private:
	Context mContext;
	vector2 mDirection;
	static constexpr float mSpeed = 50.f;

	sf::Time mTtl;
	sf::Time mCreationTime;

	sf::Vector2f mRadius;
};
