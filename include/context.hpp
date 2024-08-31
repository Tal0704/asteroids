#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

struct Context
{
	const sf::RenderWindow& window;
	const sf::Clock clock;

	Context(const sf::RenderWindow& window);
};
