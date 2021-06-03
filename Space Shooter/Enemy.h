#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RandomEngine.h"

class Enemy :
	public sf::Drawable
{
public:
	Enemy(const sf::Vector2f& position, const sf::Vector2f& velocity, int hp, const sf::Texture& textureOfEnemy);
	virtual ~Enemy();
	void update(float deltaTime);
	void takeDamage(int damage);
	int getHp() const;
	sf::FloatRect getGlobalBounds() const;
	float getRadius() const;
	sf::Vector2f getPosition() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Sprite enemy;
	float velocityOfRotating;
	sf::Vector2f velocity;
	float radius;
	int hp;
	void updateRadius();
	sf::Vector2u sizeOfTexture;
};

