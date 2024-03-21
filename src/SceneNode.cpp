#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SceneNode.hpp>

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawCurrent(target, states);
	for (const auto& child: mChildren)
	{
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}
