#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

class SceneNode:
	public sf::Drawable,
	public sf::Transformable,
	public sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	void attachChild(Ptr child);
	Ptr  detachChild(const SceneNode& child);

	virtual void update(const sf::Time& dt)final;

	const SceneNode& operator[](size_t index) const;
	const SceneNode& at(size_t index) const;

	size_t size();

	bool toRemove() const;

protected:
	bool isPendingRemoval = false;

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	virtual void updateCurrent(const sf::Time& dt);

	virtual void drawCurrent(sf::RenderTarget& traget, sf::RenderStates states) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};
