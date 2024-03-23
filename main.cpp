#include <ship.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#define FPS sf::seconds(1/60.f)
#define PI 3.14159265

sf::RenderWindow window(sf::VideoMode(460, 460), "Asteroids!");
Ship ship;

void processInput();
void update(const sf::Time& dt);
void render();

int main()
{

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
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
	#define SHEEP_SPEED 30
	#define ROT_SPEED 3
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ship.rotation += dt.asSeconds() * PI * ROT_SPEED;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ship.rotation -= dt.asSeconds() * PI * ROT_SPEED;
	}

	sf::Vector2f direction = {
		std::cos(ship.rotation), std::sin(ship.rotation)
	};

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		ship.velocity = ship.velocity + (direction * dt.asSeconds());
	}
	
	// ship.transform.rotate(ship.rotation).
}

void render()
{
	window.clear();
	window.draw(ship);
	window.display();
}
