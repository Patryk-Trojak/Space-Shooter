#include "HitboxComponent.h"

HitboxComponent::HitboxComponent()
{
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::addHitbox(const Hitbox&& hitbox)
{
	hitboxes.emplace_back(hitbox);
}

void HitboxComponent::setPositionOfHitbox(const int numberOfHitbox, const sf::Vector2f& Position)
{
	hitboxes[numberOfHitbox].setPosition(Position);
}

sf::Vector2f HitboxComponent::getOffset(const int numberOfHitbox) const
{
	return hitboxes[numberOfHitbox].getOffset();
}

void HitboxComponent::moveAllHitboxes(const sf::Vector2f& Offset)
{
	for (auto& i : hitboxes)
		i.move(Offset);
}


bool HitboxComponent::intersects(const sf::FloatRect& floatRect) const
{
	for (auto const& i : this->hitboxes)
	{
		if (i.intersects(floatRect))
		{
			return true;
		}
	}
	return false;
}

bool HitboxComponent::intersects(const HitboxComponent& hitboxComponent) const
{
	for (auto const& i : this->hitboxes)
	{
		for (auto const& j : hitboxComponent.getHitboxes())
		{
			if (i.intersects(j))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitboxComponent::intersectsWithCircle(const sf::Vector2f& centerOfCircle, float radius) const
{
	for (auto const& i : this->hitboxes)
	{
		if (i.intersectsWithCircle(centerOfCircle, radius))
		{
			return true;
		}
	}
	return false;
}


size_t HitboxComponent::size() const
{
	return hitboxes.size();
}

const std::vector<Hitbox>& HitboxComponent::getHitboxes() const
{
	return hitboxes;
}

const Hitbox& HitboxComponent::operator[](int i) const
{
	return hitboxes[i];
}
