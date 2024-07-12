#pragma once
#include <SFML/Graphics.hpp>

struct Context
{
	const sf::RenderWindow& window;

	Context(const sf::RenderWindow& window);
};
