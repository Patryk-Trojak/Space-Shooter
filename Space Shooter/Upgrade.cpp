#include "Upgrade.h"

Upgrade::Upgrade(const sf::Vector2f& position, const sf::Texture& textureOfProjectile)
	:velocity(sf::Vector2f(0.f, 500.f))
{
	upgrade.setTexture(textureOfProjectile);
	upgrade.setOrigin(textureOfProjectile.getSize().x / 2.f, textureOfProjectile.getSize().y / 2.f);
	upgrade.setPosition(position);
}

Upgrade::~Upgrade()
{
}

void Upgrade::update(float deltaTime)
{
	upgrade.move(velocity * deltaTime);
}

sf::FloatRect Upgrade::getGlobalBounds() const
{
	return upgrade.getGlobalBounds();
}

sf::Vector2f Upgrade::getPosition() const
{
	return upgrade.getPosition();
}


void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(upgrade);
}
