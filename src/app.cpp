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
		auto ast = std::make_unique<Asteroid>(mContext);
		asteroid = std::move(ast);
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

	const auto& pallets = mShip->getPallets();
	for(const auto& pallet: pallets)
		pallet->update(dt);
	processCollisions();
	if(isShipDead)
	{
		std::cout << "Dead\n";
	}
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
	std::vector<Asteroid::Ptr> asteroidsToRemove;
	asteroidsToRemove.reserve(mAsteroids.size());
	for(const auto& asteroid: mAsteroids)
	{
		if(asteroid->collideShip(*mShip))
		{
			isShipDead = true;
			/* asteroidsToRemove.emplace_back(asteroid); */
		}
	}
	/* for(const auto& asteroid: asteroidsToRemove) */
	/* { */
	/* 	auto foundAsteroid = std::find_if(mAsteroids.begin(), mAsteroids.end(), */ 
	/* 			[&](Asteroid::Ptr& a) {return a == asteroid;} ); */
	/* 	mAsteroids.erase(foundAsteroid); */
	/* } */
}

