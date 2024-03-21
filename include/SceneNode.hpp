#pragma once

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

class SceneNode
	: public sf::Drawable
{
public:
	typedef SceneNode* Ptr;
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr> mChildren;
};
