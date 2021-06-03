#pragma once
#include <SFML/Graphics.hpp>
#include "HealthBar.h"
#include "ResourceHolder.h"

class PlayerHUD
	: public sf::Drawable
{
public:
	PlayerHUD(const TexturesHolder& textures, const sf::Font& font);
	virtual ~PlayerHUD();
	
	void update(int playerHp, int numberOfCurrentWave);
private:
	HealthBar healthBar;
	sf::Text numberOfCurrentWave;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

