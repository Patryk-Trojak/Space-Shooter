#pragma once
#include <SFML/Graphics.hpp>

class Projectile : 
	public sf::Drawable
{
public:
	Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Texture& textureOfProjectile);
	virtual ~Projectile();
	void update(float deltaTime);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite projectile;
	sf::Vector2f velocity;
};

