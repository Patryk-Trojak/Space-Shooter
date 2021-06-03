#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "HitboxComponent.h"

class Player
	:public sf::Drawable
{
public:
	Player(const sf::Vector2f& mousePosition, const sf::Texture& textureOfSpaceShip, const sf::Texture& textureOfProjectile);
	virtual ~Player();

	void update(const sf::Vector2f& mousePositionRelativeToView);
	void updateShooting(std::vector < std::unique_ptr<Projectile> >& projectiles, float deltaTime);
	void addUpgrade(int value);
	int getHp() const;
	void takeDamage(int value);
	sf::FloatRect getGlobalBounds() const;
	HitboxComponent hitboxComponent;
private:
	sf::Sprite spaceShip;
	int numberOfUpgrade;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	float timerOfShooting;
	void shoot(std::vector < std::unique_ptr<Projectile> >& projectiles);
	const sf::Texture& textureOfProjectile;
	int hp;
};

