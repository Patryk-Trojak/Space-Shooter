#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class HealthBar
	: public sf::Drawable
{
public:
	HealthBar(const sf::Vector2f& Position, const sf::Texture& textureOfBackground, const sf::Texture& textureOfBar, const sf::Font& font,
		const int maxValue, const int currentValue);
	virtual ~HealthBar();
	void setValue(int newValue);
protected:
	sf::Sprite background;
	sf::Sprite bar;
	sf::Text value;
	const sf::Vector2i initialSizeOfBarTexture;
	int maxValue;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

