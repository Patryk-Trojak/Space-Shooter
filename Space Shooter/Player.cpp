#include "Player.h"

Player::Player(const sf::Vector2f& mousePosition, const sf::Texture& textureOfSpaceShip, const sf::Texture& textureOfProjectile)
	:timerOfShooting(0.f),
	textureOfProjectile(textureOfProjectile),
	numberOfUpgrade(1),
	hp(100)
{
	spaceShip.setTexture(textureOfSpaceShip);
	spaceShip.setOrigin(static_cast<float>(textureOfSpaceShip.getSize().x) / 2.f, static_cast<float>(textureOfSpaceShip.getSize().y) / 2.f);
	spaceShip.setPosition(mousePosition);

	
	hitboxComponent.addHitbox(Hitbox(mousePosition, sf::Vector2f(90.0003f, 36.0003f), sf::Vector2f(-45.0004f, -0.00167847f)));
	hitboxComponent.addHitbox(Hitbox(mousePosition, sf::Vector2f(78.0043f, 53.9966f), sf::Vector2f(-39.0044f, -11.9953f)));
	hitboxComponent.addHitbox(Hitbox(mousePosition, sf::Vector2f(66.0159f, 65.6637f), sf::Vector2f(-33.0069f, -23.9821f)));
	hitboxComponent.addHitbox(Hitbox(mousePosition, sf::Vector2f(54.0097f, 83.9995f), sf::Vector2f(-27.0086f, -35.9968f)));
	hitboxComponent.addHitbox(Hitbox(mousePosition, sf::Vector2f(42.0732f, 94.074f), sf::Vector2f(-20.9933f, -48.1082f)));
}

Player::~Player()
{
}

void Player::update(const sf::Vector2f& mousePositionRelativeToView)
{
	spaceShip.setPosition(mousePositionRelativeToView);
	for (size_t i = 0; i < hitboxComponent.size(); i++)
	{
		hitboxComponent.setPositionOfHitbox(i, mousePositionRelativeToView + hitboxComponent.getOffset(i));
	}
}

void Player::updateShooting(std::vector < std::unique_ptr<Projectile> >& projectiles, float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		timerOfShooting += deltaTime;
		if (timerOfShooting >= 0.03f)
		{
			shoot(projectiles);
			timerOfShooting -= 0.03f;
		}
	}
}

void Player::addUpgrade(int value)
{
	numberOfUpgrade += value;
	if (numberOfUpgrade > 19)
		numberOfUpgrade = 19;
}

int Player::getHp() const
{
	return hp;
}

void Player::takeDamage(int value)
{
	hp -= value;
	if (hp < 0)
		hp = 0;
}

sf::FloatRect Player::getGlobalBounds() const
{
	return spaceShip.getGlobalBounds();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spaceShip, states);
}

void Player::shoot(std::vector<std::unique_ptr<Projectile>>& projectiles)
{
	int numberOfProjectileToShot = numberOfUpgrade;
	if (numberOfUpgrade % 2 == 1)
	{
		projectiles.emplace_back(std::make_unique<Projectile>(spaceShip.getPosition() + sf::Vector2f(0, -45), sf::Vector2f(0, -1500.f), textureOfProjectile));
		numberOfProjectileToShot--; 
	}

	for(int i = 0; i < numberOfProjectileToShot / 2; i++)
		projectiles.emplace_back(std::make_unique<Projectile>(spaceShip.getPosition() + sf::Vector2f(-12, -65), sf::Vector2f(- i * 50.f, -1500.f), textureOfProjectile));
	
	for(int i = 0; i < numberOfProjectileToShot / 2; i++)
		projectiles.emplace_back(std::make_unique<Projectile>(spaceShip.getPosition() + sf::Vector2f(12, -65), sf::Vector2f(i * 50.f, -1500.f), textureOfProjectile));
}

