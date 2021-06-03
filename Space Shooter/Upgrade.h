#pragma once
#include<SFML/Graphics.hpp>

class Upgrade
	: public sf::Drawable
{
public:
	Upgrade(const sf::Vector2f& position, const sf::Texture& textureOfUpgrade);
	virtual ~Upgrade();
	void update(float deltaTime);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite upgrade;
	sf::Vector2f velocity;
};

