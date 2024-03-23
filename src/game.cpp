#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <game.hpp>

#define FPS sf::seconds(1/60.f)

Game::Game()
	: mWindow(sf::VideoMode(460, 460), "Asteroids!")
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while(timeSinceLastUpdate > FPS)
		{
			timeSinceLastUpdate -= FPS;
			processInput();
			update(FPS);
		}
		render();
	}
}

void Game::processInput()
{
	while(mWindow.pollEvent(mEvent))
	{
		if(mEvent.type == sf::Event::Closed)
			mWindow.close();

		if(mEvent.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		
		mWorld.handleEvent(mEvent);
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mWorld);
	mWindow.display();
}

void Game::update(const sf::Time& dt)
{
	mWorld.update(dt);
}
