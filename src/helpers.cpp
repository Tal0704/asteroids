#include <helpers.hpp>

using namespace help;

template <typename T>
T distance(const sf::Vector2<T>& v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

template <typename T>
sf::Vector2<T> normalize(const sf::Vector2<T>& v)
{
	const T d = distance(v);
	return sf::Vector2<T>(v.x / d, v.y / d);
}

#ifndef NDEBUG
template <typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& v)
{
	stream << v.x << ", " << v.y;
	return stream;
}
#endif

