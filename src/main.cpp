#include <memory>
#include <ship.hpp>
#include <asteroid.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define FPS sf::seconds(1/60.f)
#define PI 3.14159265

sf::RenderWindow window(sf::VideoMode(460, 460), "Asteroids!");
Ship::Ptr ship;
std::vector<Asteroid::Ptr> asteroids;

void processInput();
void update(const sf::Time& dt);
void render();

int main()
{
	ship = std::make_unique<Ship>(sf::Vector2f(window.getSize()));
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	asteroids.resize(4);
	for(size_t i = 0; i < 4; i++)
	{
		asteroids[i] = std::make_unique<Asteroid>();
	}
	while(window.isOpen())
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
	
	return 0;
}


void processInput()
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void update(const sf::Time& dt)
{
	ship->update(dt);
	for(auto& asteroid: asteroids)
		asteroid->update(dt);
}

void render()
{
	window.clear();
	window.draw(*ship);
	for(const auto& asteroid: asteroids)
		window.draw(*asteroid);
	window.display();
}
