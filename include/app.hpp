#pragma once
#include <SFML/Graphics.hpp>
#include <asteroid.hpp>
#include <context.hpp>
#include <ship.hpp>

class App
{
public:
	App();

	void run();

private:
	void processInput();
	void render();
	void update(const sf::Time& dt);

	sf::RenderWindow mWindow;
	Context mContext;
	std::vector<Asteroid::Ptr> mAsteroids;
	std::unique_ptr<Ship> mShip;
	sf::Event mEvent;

	sf::Clock mClock;

	const sf::Time fps = sf::seconds(1/60.f);
};
