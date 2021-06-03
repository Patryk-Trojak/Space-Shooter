#pragma once
#include <vector>
#include <iostream>
#include "State.h"
#include "Projectile.h"
#include "Player.h"
#include "RandomEngine.h"
#include "Enemy.h"
#include "CollisionsHandler.h"
#include "PlayerHUD.h"
#include "Upgrade.h"
#include "ParticleSystem.h"


class GameplayState
	:public State
{
public:
	GameplayState(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font);
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Player player;
	std::vector < std::unique_ptr<Projectile> > projectiles;
	std::vector < std::unique_ptr<Enemy> > enemies;
	std::vector < std::unique_ptr<Upgrade> > upgrades;
	ParticleSystem particleSystem;

	void updateProjectiles(float deltaTime);
	void updateEnemies(float deltaTime);
	void updateUpgrades(float deltaTime);

	void handleCreatingEnemies(float deltaTime);
	void eraseProjectileIfItOutOfScreen();
	void tryEndGame();
	bool isEnemyUnderTheScreen();
	bool end;
	float timerOfCreatingEnemies;
	float timerBetweenWaves;
	bool isWave;
	int maxNumberOfEnemiesInWave;
	int numberOfSpawnedEnemiesInWave;
	int numberOfWave;
	float timeBetweenSpawningEnemies;
	PlayerHUD playerHUD;

	sf::Text infoAboutLost;

	CollisionsHandler collisionsHandler;
};

