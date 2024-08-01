#pragma once
#include <functional>
#include <SFML/System/Time.hpp>

struct Command
{
	std::function<void(const sf::Time)> action();
};
