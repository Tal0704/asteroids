#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <world.hpp>

class Game
{
public:
	Game();
	void run();
	void processInput();
	void render();
	void update(const sf::Time& dt);

private:
	sf::RenderWindow mWindow;
	sf::Event mEvent;
 	World mWorld;
};

