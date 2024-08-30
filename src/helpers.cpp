#include <helpers.hpp>
#include <complex>

float angleFromVect(const sf::Vector2f& v)
{
	std::complex c(v.x, v.y);
	return std::arg(c) * 180 / PI;
}

float distance(const sf::Vector2f& left, const sf::Vector2f& right)
{
	return std::sqrt(std::pow(left.x - right.x, 2) + std::pow(left.y - right.y, 2));
}

sf::Vector2f velocityFromSpeed(float speed, float angle)
{
	sf::Vector2f direction;
	direction.x = speed * std::cos(angle * PI / 180 + 0.5 * PI);
	direction.y = speed * std::sin(angle * PI / 180 + 0.5 * PI);

	return direction;
}
