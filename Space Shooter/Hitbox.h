#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Hitbox
	:public sf::Drawable
{
public:
	Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset = sf::Vector2f(0.f, 0.f), const sf::Color& color = sf::Color(255, 0, 0, 150));
	virtual ~Hitbox();
	void setPosition(const sf::Vector2f& Position);

	void move(const sf::Vector2f& Offset);

	const sf::FloatRect& getGlobalBounds() const;
	const sf::Vector2f& getOffset() const;

	bool intersects(const Hitbox& hitbox2) const;
	bool intersects(const sf::FloatRect& floatRect) const;
	bool intersectsWithCircle(const sf::Vector2f& center, float radius) const;
private:
	sf::RectangleShape hitbox;
	sf::Vector2f offset;
	sf::FloatRect globalBounds;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	float clamp(float value, float min, float max) const;

};


