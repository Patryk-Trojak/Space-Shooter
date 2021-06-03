#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(const TexturesHolder& textures, const sf::Font& font)
	:healthBar(sf::Vector2f(50.f, 1000.f), textures.getResource(TextureID::healthBarBackground), textures.getResource(TextureID::healthBarValue), font,
		100, 100),
	numberOfCurrentWave("Faza: 1", font, 50)
{
	numberOfCurrentWave.setPosition(300.f, 990.f);
}

PlayerHUD::~PlayerHUD()
{
}

void PlayerHUD::update(int playerHp, int numberOfCurrentWave)
{
	healthBar.setValue(playerHp);
	this->numberOfCurrentWave.setString("Faza " + std::to_string(numberOfCurrentWave) );
}

void PlayerHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(healthBar);
	target.draw(numberOfCurrentWave);
}
