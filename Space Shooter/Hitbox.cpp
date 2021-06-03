#include "Hitbox.h"


Hitbox::Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset, const sf::Color& color)
	:hitbox(Size),
	offset(Offset)
{
	hitbox.setPosition(Position + Offset);
	//hitbox.setOutlineColor(sf::Color::Red);
	//hitbox.setOutlineThickness(0);
	{
		//hitbox.setFillColor(sf::Color(255, 0, 0, 70));
		//hitbox.setFillColor(sf::Color(255, 0, 0, 190));
		hitbox.setFillColor(color);
	}

	globalBounds = hitbox.getGlobalBounds();
}

Hitbox::~Hitbox()
{
}


void Hitbox::setPosition(const sf::Vector2f& Position)
{
	hitbox.setPosition(Position);
	globalBounds = hitbox.getGlobalBounds();
}


void Hitbox::move(const sf::Vector2f& Offset)
{
	hitbox.move(Offset);
	globalBounds = hitbox.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getGlobalBounds() const
{
	return globalBounds;
}


const sf::Vector2f& Hitbox::getOffset() const
{
	return offset;
}


bool Hitbox::intersects(const Hitbox& hitbox2) const
{
	if (globalBounds.left + globalBounds.width > hitbox2.getGlobalBounds().left)
	{
		if (globalBounds.left < hitbox2.getGlobalBounds().left + hitbox2.getGlobalBounds().width)
		{
			if (globalBounds.top + globalBounds.height > hitbox2.getGlobalBounds().top)
			{
				if (globalBounds.top < hitbox2.getGlobalBounds().top + hitbox2.getGlobalBounds().height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Hitbox::intersects(const sf::FloatRect& floatRect) const
{
	if (globalBounds.left + globalBounds.width > floatRect.left)
	{
		if (globalBounds.left < floatRect.left + floatRect.width)
		{
			if (globalBounds.top + globalBounds.height > floatRect.top)
			{
				if (globalBounds.top < floatRect.top + floatRect.height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Hitbox::intersectsWithCircle(const sf::Vector2f& center, float radius) const
{
	sf::Vector2f closestPointInRectangle;
	closestPointInRectangle.x = clamp(center.x, globalBounds.left, globalBounds.left + globalBounds.width);
	closestPointInRectangle.y = clamp(center.y, globalBounds.top, globalBounds.top + globalBounds.height);
	

	if (closestPointInRectangle == center)
	{
		return true;
	}
	
	sf::Vector2f vectorBetweenCenterAndClosestPoint = closestPointInRectangle - center;

	float distanceSquared = std::pow(vectorBetweenCenterAndClosestPoint.x, 2) + std::pow(vectorBetweenCenterAndClosestPoint.y, 2);

	if (distanceSquared < std::pow(radius, 2))
	{
		return true;
	}

	return false;
}

void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(hitbox, state);
}

float Hitbox::clamp(float value, float min, float max) const
{
	if (value < min)
		return min;
	else if (value > max)
		return max;

	return value;
}
