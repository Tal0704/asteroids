#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class SceneNode: public sf::Drawable
{
public:
	typedef SceneNode* Ptr;

private:
	Ptr mFather = nullptr;
	std::vector<Ptr> mChildren;
};
