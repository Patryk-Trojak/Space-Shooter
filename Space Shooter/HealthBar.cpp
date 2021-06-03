#include "HealthBar.h"


HealthBar::HealthBar(const sf::Vector2f& Position, const sf::Texture& textureOfBackground, const sf::Texture& textureOfBar, const sf::Font& font,
	const int maxValue, const int currentValue)
	:maxValue(maxValue),
	initialSizeOfBarTexture(textureOfBar.getSize())
{
	background.setTexture(textureOfBackground);
	background.setPosition(Position );
	bar.setTexture(textureOfBar);
	bar.setPosition(Position + sf::Vector2f(57.f, 3.f));

	value.setFont(font);
	value.setOutlineColor(sf::Color::Black);
	value.setOutlineThickness(2);
	setValue(currentValue);

	value.setOrigin(0.f, 10.f);
	
}

HealthBar::~HealthBar()
{
}

void HealthBar::setValue(int newValue)
{
	bar.setTextureRect(sf::IntRect(0, 0, static_cast<float>(newValue) / maxValue * initialSizeOfBarTexture.x, initialSizeOfBarTexture.y));
	value.setString(std::to_wstring(newValue) + L"/" + std::to_wstring(maxValue));
	value.setPosition(bar.getPosition() + sf::Vector2f((bar.getTexture()->getSize().x - value.getGlobalBounds().width) / 2, (bar.getTexture()->getSize().y - value.getGlobalBounds().height) / 2));
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(bar, states);
	target.draw(value, states);
}
