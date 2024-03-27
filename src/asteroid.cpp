#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include <asteroid.hpp>
#include <random>

#define PI 3.14159265
#define SCALE sf::Vector2f(30.0f, 30.f)
#define ORIGIN sf::Vector2f(150.f, 150.f)

Asteroid::Asteroid()
	:mVertecies(sf::PrimitiveType::LineStrip)
{
	float radius;

	std::random_device r;
	std::default_random_engine e(r());

	std::uniform_int_distribution<size_t> uniformIntDist(8, 10);
	mVertecies.resize(uniformIntDist(e));

	std::uniform_real_distribution<float> uniformFloatDist(0.4, 0.8);

	for(size_t i = 0; i < mVertecies.getVertexCount(); i++)
	{
		radius = uniformFloatDist(e);
		float angle = 2 * PI / mVertecies.getVertexCount();
		angle *= i;
		mVertecies[i].position = sf::Vector2f(radius * std::cos(angle), std::sin(angle) * radius);
	}
	mVertecies.append(mVertecies[0]);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(ORIGIN + position).scale(SCALE);

	target.draw(mVertecies, states);
}
