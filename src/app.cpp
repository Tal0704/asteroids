#include <app.hpp>

App::App()
	: mWindow(sf::VideoMode({400, 400}), "Asteroids!!")
	, mContext(mWindow)
	, mShip(std::make_unique<Ship>(mContext))
	, mDebugFont("media/fonts/PressStart2P.ttf")
	, mDebugText(mDebugFont)
{ 
	mWindow.setKeyRepeatEnabled(true);
	mAsteroids.reserve(10);
	for(size_t i = 0; i < mAsteroids.capacity(); i++)
	{
		mAsteroids.emplace_back(std::make_unique<Asteroid>(mContext));
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
			processInput(timeSinceLastUpdate);
			update(fps);
		}
		render();
	}
}

void App::processInput(const sf::Time& dt)
{
	while((mEvent = mWindow.pollEvent()))
	{
		mShip->processInput(mEvent);
		bool isClose = (mEvent->is<sf::Event::Closed>()) || 
			(mEvent->is<sf::Event::KeyPressed>() && mEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q);
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
	static sf::Time timeSinceStart = dt;
	if (timeSinceStart >= sf::seconds(1)) {
		processCollisions();
	} else {
		timeSinceStart += dt;
	}

	if(mShip->isDead())
		mWindow.close();
}

void App::render() {
	mWindow.clear();
	mWindow.draw(*mShip);
	const auto& pallets = mShip->getPallets();
	for(const auto& pallet: pallets)
		mWindow.draw(*pallet);
	for(const auto& asteroid: mAsteroids)
		mWindow.draw(*asteroid);
	mWindow.draw(mDebugText);
	mWindow.display();
}

void App::processCollisions()
{
	const auto& pallets = mShip->getPallets();

	for(const auto& pallet: pallets)
	{
		if(mShip->collidePallet(*pallet))
		{
			mShip->destroy();
		}

		for(auto& asteroid: mAsteroids)
		{
			if(pallet->collideAsteroid(*asteroid))
			{
				asteroid->kill();
			}
		}
	}

	for(auto& asteroid: mAsteroids)
	{
		if(mShip->collideAsteroid(*asteroid))
		{
			asteroid->kill();
			mShip->destroy();
		}
	}

	std::erase_if(mAsteroids, [&](const Asteroid::Ptr& asteroid) -> bool {
				return asteroid->isFinishedExplosion();
			});
}
