#include "SFML/System/Vector2.hpp"
#include <memory>
#include <ship.hpp>
#include <asteroid.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
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
	ship = std::make_unique<Ship>();
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	asteroids.resize(4);
	for(size_t i = 0; i < 4; i++)
	{
		asteroids[i] = std::make_unique<Asteroid>();
		asteroids[i]->position = sf::Vector2f(i * 50, i * 50);
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
	#define SHIP_SPEED 10.f
	#define ROT_SPEED 600
	#define DRAG 0.02
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ship->rotation -= dt.asSeconds() * ROT_SPEED;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ship->rotation += dt.asSeconds() * ROT_SPEED;
	}

	sf::Vector2f direction;
	direction.x = std::cos(ship->rotation * PI / 180 + 0.5 * PI);
	direction.y = std::sin(ship->rotation * PI / 180 + 0.5 * PI);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		ship->velocity = ship->velocity + (direction * dt.asSeconds() * SHIP_SPEED);
	}
	ship->velocity.x *= 1.0 - DRAG;
	ship->velocity.y *= 1.0 - DRAG;
	ship->position += ship->velocity;
}

void render()
{
	window.clear();
	window.draw(*ship);
	for(const auto& asteroid: asteroids)
		window.draw(*asteroid);
	window.display();
}
