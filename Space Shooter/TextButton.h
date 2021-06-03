#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class ContentAlignment { center = 0, left, right };
enum class ButtonState { idle = 0, hover };

class TextButton
	:public sf::Drawable
{
public:
	TextButton(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& Texture, const sf::Font& Font,
		const std::wstring Text, const unsigned CharacterSize);
	virtual ~TextButton();
	void update(const sf::Vector2f& mousePosition);
	bool wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const;

	bool isMouseOverButton(const sf::Vector2f& mousePosition) const;
protected:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Color IdleColor;
	sf::Color HoverColor;
	ButtonState state;

	void updateColorByButtonState();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
