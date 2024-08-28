#pragma once
#include <SFML/System/Vector2.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

namespace help
{
	template <typename T>
		sf::Vector2<T> normalize(const sf::Vector2<T>& v);
	template <typename T>
	T distance(const sf::Vector2<T>& v);

template <typename T>
	std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& v);
}
