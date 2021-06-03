#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, const sf::Vector2f& velocity, int hp, const sf::Texture& textureOfEnemy)
	:velocity(velocity),
	hp(hp)
{
	enemy.setOrigin(static_cast<float>(textureOfEnemy.getSize().x) / 2.f, static_cast<float>(textureOfEnemy.getSize().y) / 2.f);
	enemy.setTexture(textureOfEnemy);
	enemy.setPosition(position);
	updateRadius();
	enemy.setScale(radius * 2.f / textureOfEnemy.getSize().x, radius * 2.f / textureOfEnemy.getSize().x);

	sizeOfTexture = textureOfEnemy.getSize();
	velocityOfRotating = static_cast<float>(RandomEngine::randInt(-100, 100));
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	enemy.move(velocity * deltaTime);
	enemy.rotate(velocityOfRotating * deltaTime);
}

void Enemy::takeDamage(int damage)
{
	hp -= damage;
	updateRadius();
	enemy.setScale(radius * 2.f / sizeOfTexture.x, radius * 2.f / sizeOfTexture.x);
}

int Enemy::getHp() const
{
	return hp;
}

sf::FloatRect Enemy::getGlobalBounds() const
{
	return enemy.getGlobalBounds();
}

float Enemy::getRadius() const
{
	return radius;
}

sf::Vector2f Enemy::getPosition() const
{
	return enemy.getPosition();
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(enemy);
}

void Enemy::updateRadius()
{
	radius = 40.f + hp / 5.f;
}
