#include <app.hpp>

App::App()
	: mWindow(sf::VideoMode(400, 400), "Asteroids!!")
	, mContext(mWindow)
	, mShip(std::make_unique<Ship>(mContext))
{ 
	mWindow.setKeyRepeatEnabled(false);
	mAsteroids.resize(10);
	for(auto& asteroid: mAsteroids)
	{
		asteroid = std::make_unique<Asteroid>();
	}
}

void App::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(mWindow.isOpen())
	{
		sf::Time dt = mClock.restart();
		timeSinceLastUpdate += dt;
		while(timeSinceLastUpdate > fps)
		{
			timeSinceLastUpdate -= fps;
			processInput();
			update(fps);
		}
		render();
	}
}

void App::processInput()
{
	while(mWindow.pollEvent(mEvent))
	{
		mShip->processInput(mEvent);
		bool isClose = (mEvent.type == sf::Event::Closed) || ((mEvent.type == sf::Event::KeyPressed) && mEvent.key.code == sf::Keyboard::Q);
		if (isClose)
			mWindow.close();
	}
}

void App::update(const sf::Time& dt)
{
	mShip->update(dt);
	for(auto& asteroid: mAsteroids)
		asteroid->update(dt);
}

void App::render()
{
	mWindow.clear();
	mWindow.draw(*mShip);
	for(const auto& asteroid: mAsteroids)
		mWindow.draw(*asteroid);
	mWindow.display();
}
