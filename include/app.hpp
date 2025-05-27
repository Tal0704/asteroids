#pragma once
#include <SFML/Graphics.hpp>
#include <asteroid.hpp>
#include <context.hpp>
#include <optional>
#include <ship.hpp>
#include <memory>
#include <vector>

class App
{
public:
	App();

	void run();

private:
	void processInput(const sf::Time& dt);
	void render();
	void update(const sf::Time& dt);
	void updatePressedKeys();

	void processCollisions();

	void dead();

	sf::RenderWindow mWindow;
	Context mContext;
	std::vector<Asteroid::Ptr> mAsteroids;
	std::unique_ptr<Ship> mShip;
	std::optional<sf::Event> mEvent;

	sf::Clock mClock;

	const sf::Time fps = sf::seconds(1/60.f);

	sf::Font mDebugFont;
	sf::Text mDebugText;
};
