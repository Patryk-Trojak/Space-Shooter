#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Texture& textureOfProjectile)
	:velocity(velocity)
{
	projectile.setTexture(textureOfProjectile);
	projectile.setOrigin(textureOfProjectile.getSize().x / 2.f, textureOfProjectile.getSize().y / 2.f);
	projectile.setPosition(position);
}

Projectile::~Projectile()
{
}

void Projectile::update(float deltaTime)
{
	projectile.move(velocity * deltaTime);
}

sf::FloatRect Projectile::getGlobalBounds() const
{
	return projectile.getGlobalBounds();
}

sf::Vector2f Projectile::getPosition() const
{
	return projectile.getPosition();
}


void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(projectile);
}

