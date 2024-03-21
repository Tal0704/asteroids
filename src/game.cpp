#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <game.hpp>

Game::Game()
	: mWindow(sf::VideoMode(460, 460), "Asteroids!")
{
}

void Game::run()
{
	while(mWindow.isOpen())
	{
		while(mWindow.pollEvent(mEvent))
		{
			if(mEvent.type == sf::Event::Closed)
				mWindow.close();
		}
		processInput();
		render();
	}
}

void Game::processInput()
{
	while(mWindow.pollEvent(mEvent))
	{
		if(mEvent.type == sf::Event::Closed)
		{
			mWindow.close();
		}


	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mWorld);
	mWindow.display();
}
