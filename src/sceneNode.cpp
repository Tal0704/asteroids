#include <cassert>
#include <sceneNode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>

using sn = SceneNode;

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for(const auto& child: mChildren)
	{
		child->draw(target, states);
	}
}

void SceneNode::updateCurrent(const sf::Time& dt)
{
}

void SceneNode::update(const sf::Time& dt)
{
	updateCurrent(dt);
	for (auto& child: mChildren)
		child->update(dt);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}

void sn::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

sn::Ptr SceneNode::detachChild(const sn& child)
{
	auto foundVal = std::find_if(mChildren.begin(), mChildren.end(), [&](sn::Ptr& p) -> bool {
				return p.get() == &child;
				});
	assert(foundVal != mChildren.end());
	Ptr result = std::move(*foundVal);
	result->mParent = nullptr;
	mChildren.erase(foundVal);
	return std::move(result);
}
