#include <app.hpp>

App::App()
	: mWindow(sf::VideoMode(400, 400), "Asteroids!!")
	, mContext(mWindow)
	, mShip(std::make_unique<Ship>(mContext))
{ 
	mWindow.setKeyRepeatEnabled(false);
	const size_t numOfAsteroids = 5;
	mAsteroids.reserve(numOfAsteroids);
	for(size_t i = 0; i < numOfAsteroids; i++)
	{
		mAsteroids.emplace_back(std::make_unique<Asteroid>(mContext));
	}
#ifndef NDEBUG
	mFont.loadFromFile("media/fonts/PressStart2P.ttf");
	mDebugText.setFont(mFont);
	mDebugText.setCharacterSize(10);
	mDebugText.setFillColor(sf::Color::Green);
	mDebugText.setString("pallet didn't hit the ship!");
#endif
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
#ifndef NDEBUG
	if(isShipDead)
		std::cout << "Dead\n";
#endif
}

void App::render()
{
	mWindow.clear();
	mWindow.draw(mDebugText);
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
	std::vector<Asteroid::Ptr> asteroidsToRemove;
	asteroidsToRemove.reserve(mAsteroids.size());
	const auto& pallets = mShip->getPallets();

	for(const auto& pallet: pallets)
	{
		if(mShip->getGlobalBounds().contains(pallet->getPosition()))
		{
			isShipDead = true;
		}
	}

	for(const auto& asteroid: mAsteroids)
	{
		if(mShip->collideAsteroid(*asteroid))
		{
			mDebugText.setFillColor(sf::Color::Red);
			mDebugText.setString("pallet hit the ship!");
		}
		else
		{
			mDebugText.setFillColor(sf::Color::Green);
			mDebugText.setString("pallet didn't hit the ship!");
		}
	}
	/* for(const auto& asteroid: asteroidsToRemove) */
	/* { */
	/* 	auto foundAsteroid = std::find_if(mAsteroids.begin(), mAsteroids.end(), */ 
	/* 			[&](Asteroid::Ptr& a) {return a == asteroid;} ); */
	/* 	mAsteroids.erase(foundAsteroid); */
	/* } */
}
