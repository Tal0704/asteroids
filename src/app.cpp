#include <app.hpp>

App::App()
	: mWindow(sf::VideoMode(400, 400), "Asteroids!!")
	, mContext(mWindow)
	, mShip(std::make_unique<Ship>(mContext))
{ 
	mWindow.setKeyRepeatEnabled(false);
	const size_t numOfAsteroids = 10;
	mAsteroids.reserve(numOfAsteroids);
	for(size_t i = 0; i < numOfAsteroids; i++)
	{
		mAsteroids.emplace_back(std::make_unique<Asteroid>(mContext));
	}
	mFont.loadFromFile("media/fonts/PressStart2P.ttf");
	mText.setFont(mFont);
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
	mShip->processRealTime();
}

void App::update(const sf::Time& dt)
{
	mShip->update(dt);
	for(auto& asteroid: mAsteroids)
		asteroid->update(dt);

	const auto& pallets = mShip->getPallets();
	for(const auto& pallet: pallets)
		pallet->update(dt);
	processCollisions();
	if(isShipDead)
		mWindow.close();
}

void App::render()
{
	mWindow.clear();
	mWindow.draw(*mShip);
	const auto& pallets = mShip->getPallets();
	for(const auto& pallet: pallets)
		mWindow.draw(*pallet);
	for(const auto& asteroid: mAsteroids)
		mWindow.draw(*asteroid);
	mWindow.display();
}

void App::processCollisions()
{
	std::vector<size_t> asteroidsToRemove;
	asteroidsToRemove.reserve(mAsteroids.size());
	const auto& pallets = mShip->getPallets();

	for(const auto& pallet: pallets)
	{
		if(mShip->collidePallet(*pallet))
		{
			isShipDead = true;
		}

		for(size_t i = 0; i < mAsteroids.size(); i++)
		{
			const Asteroid::Ptr& asteroid = mAsteroids[i];
			if(pallet->collideAsteroid(*asteroid))
			{
				asteroidsToRemove.emplace_back(i);
			}
		}
	}

	for(const auto& asteroid: mAsteroids)
	{
		if(mShip->collideAsteroid(*asteroid))
		{
			isShipDead = true;
		}
	}

	for(size_t i = 0; i < asteroidsToRemove.size(); i++)
	{
		mAsteroids.erase(mAsteroids.begin() + asteroidsToRemove[i]);
	}
}
