#include "CollisionsHandler.h"

CollisionsHandler::CollisionsHandler(Player& player, 
	std::vector<std::unique_ptr<Projectile>>& projectiles, 
	std::vector<std::unique_ptr<Enemy>>& enemies,
	std::vector < std::unique_ptr<Upgrade> >& upgrades,
	ParticleSystem& particleSystem,
	const TexturesHolder& textureHolder )
	: player(player), projectiles(projectiles), enemies(enemies), upgrades(upgrades), particleSystem(particleSystem), textureHolder(textureHolder)
{
}

void CollisionsHandler::projectilesAndEnemies()
{
	auto enemy = enemies.begin();
	bool wasEnemyDeleted = false;
	while (!enemies.empty())
	{
		bool isLastEnemy = false;
		if (enemy == enemies.end() - 1)
			isLastEnemy = true;

		wasEnemyDeleted = false;
		auto projectile = projectiles.begin();
		while (!projectiles.empty())
		{
			bool isLastProjectile = false;
			if (projectile == projectiles.end() - 1)
				isLastProjectile = true;

			if (intersects(*(*projectile), *(*enemy)))
			{
				(*enemy)->takeDamage(20);
				particleSystem.add((*enemy)->getPosition(), 150);
				if ((*enemy)->getHp() <= 0)
				{
					if (RandomEngine::randInt(1, 30) == 2)
						upgrades.emplace_back(std::make_unique<Upgrade>((*enemy)->getPosition(), textureHolder.getResource(TextureID::upgrade)));

					fastErase(enemies, enemy);
					wasEnemyDeleted = true;
					break;
				}
				
				fastErase(projectiles, projectile);
			}
			else
			{
				projectile++;
			}

			if (isLastProjectile)
				break;
		}
		if (!wasEnemyDeleted)
			enemy++;

		if (isLastEnemy)
			break;
	}

}

void CollisionsHandler::playerAndEnemies()
{
	auto enemy = enemies.begin();
	while (!enemies.empty())
	{
		bool isLastElement = false;
		if (enemy == enemies.end() - 1)
			isLastElement = true;

		if (intersects(player, *(*enemy)))
		{
			player.takeDamage(10);
			fastErase(enemies, enemy);
		}
		else
		{
			enemy++;
		}
		if (isLastElement)
			break;
	}
}

void CollisionsHandler::playerAndUpgrades()
{
	auto upgrade = upgrades.begin();
	while (!upgrades.empty())
	{
		bool isLastElement = false;
		if (upgrade == upgrades.end() - 1)
			isLastElement = true;

		if (player.hitboxComponent.intersects( (*upgrade)->getGlobalBounds() ))
		{
			player.addUpgrade(1);
			fastErase(upgrades, upgrade);
		}
		else
		{
			upgrade++;
		}

		if (isLastElement)
			break;
	}
}

bool CollisionsHandler::intersects(const sf::FloatRect& first, const sf::FloatRect& second)
{
	if (first.left + first.width >= second.left)
	{
		if (first.left <= second.left + second.width)
		{
			if (first.top + first.height >= second.top)
			{
				if (first.top <= second.top + second.height)
				{
					return true;
				}
			}
		}
	}
	return false;
}

inline bool CollisionsHandler::intersects(const Projectile& projectile, const Enemy& enemy)
{
	if (intersects(projectile.getGlobalBounds(), enemy.getGlobalBounds()))
	{
		if (intersectsWithCircle(projectile.getGlobalBounds(), enemy.getPosition(), enemy.getRadius()))
			return true;
	}
	return false;
}

inline bool CollisionsHandler::intersects(const Player& player, const Enemy& enemy)
{
	if( intersects(player.getGlobalBounds(), enemy.getGlobalBounds()) )
	{
		if (player.hitboxComponent.intersectsWithCircle(enemy.getPosition(), enemy.getRadius()))
			return true;
	}
	return false;
}

inline bool CollisionsHandler::intersectsWithCircle(const sf::FloatRect& first, const sf::Vector2f& centerOfCirle, float radius)
{
	sf::Vector2f closestPointInRectangle;
	closestPointInRectangle.x = clamp(centerOfCirle.x, first.left, first.left + first.width);
	closestPointInRectangle.y = clamp(centerOfCirle.y, first.top, first.top + first.height);


	if (closestPointInRectangle == centerOfCirle)
	{
		return true;
	}

	sf::Vector2f vectorBetweenCenterAndClosestPoint = closestPointInRectangle - centerOfCirle;

	float distanceSquared = std::pow(vectorBetweenCenterAndClosestPoint.x, 2) + std::pow(vectorBetweenCenterAndClosestPoint.y, 2);

	if (distanceSquared < std::pow(radius, 2))
	{
		return true;
	}

	return false;
}

float CollisionsHandler::clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;

	return value;
}
