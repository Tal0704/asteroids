#include <game.hpp>
#include <memory>

int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();

	game->run();

	return 0;
}
