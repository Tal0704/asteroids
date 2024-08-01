#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>

class SceneNode:
	public sf::Drawable,
	public sf::Transformable,
	public sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	void attachChild(Ptr child);
	Ptr  detachChild(const SceneNode& child);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;

	virtual void drawCurrent(sf::RenderTarget& traget, sf::RenderStates states) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};
