#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include "State.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "Upgrade.h"
#include "RandomEngine.h"
#include "ResourceHolder.h"
#include "ParticleSystem.h"

class CollisionsHandler
{
public:
	CollisionsHandler(Player& player,
	std::vector < std::unique_ptr<Projectile> >&projectiles,
	std::vector < std::unique_ptr<Enemy> >& enemies,
	std::vector < std::unique_ptr<Upgrade> >& upgrades,
	ParticleSystem& particleSystem,
	const TexturesHolder& textureHolder
	);

	void projectilesAndEnemies();
	void playerAndEnemies();
	void playerAndUpgrades();
private:
	Player& player;
	std::vector < std::unique_ptr<Projectile> >& projectiles;
	std::vector < std::unique_ptr<Enemy> >& enemies;
	std::vector < std::unique_ptr<Upgrade> >& upgrades;
	ParticleSystem& particleSystem;
	const TexturesHolder& textureHolder;

	inline bool intersects(const sf::FloatRect& first, const sf::FloatRect& second);
	inline bool intersects(const Projectile& projectile, const Enemy& enemy);
	inline bool intersects(const Player& player, const Enemy& enemy);
	inline bool intersectsWithCircle(const sf::FloatRect& first, const sf::Vector2f& centerOfCirle, float radius);
	float clamp(float value, float min, float max);


	template<class ValueType>
	void fastErase(
		typename std::vector<ValueType>& container,
		typename std::vector<ValueType>::iterator it
	);

};


template<class ValueType>
inline void CollisionsHandler::fastErase(typename std::vector<ValueType>& container, typename std::vector<ValueType>::iterator it)
{//the faster way to erase element from vector but it change the order of vector
	auto lastEl = container.end() - 1;
	if (it != lastEl) {
		*it = std::move(*lastEl);
	}
	container.pop_back();
}

