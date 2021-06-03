#include "TextButton.h"

TextButton::TextButton(const sf::Vector2f& Position, const sf::Vector2f& Size,
	const sf::Texture& Texture, const sf::Font& Font,
	const std::wstring Text, const unsigned CharacterSize)
	:IdleColor(sf::Color::White), HoverColor(sf::Color::Red)
{
	state = ButtonState::idle;
	shape.setPosition(Position);
	shape.setSize(Size);
	shape.setTexture(&Texture);

	text.setString(Text);
	text.setCharacterSize(CharacterSize);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setFont(Font);
	text.setOrigin(sf::Vector2f(0.f, text.getCharacterSize() * 0.4f));
	text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, shape.getPosition().y + shape.getSize().y / 2 - text.getCharacterSize() * 0.3f );
}

TextButton::~TextButton()
{
}

void TextButton::update(const sf::Vector2f& mousePosition)
{
	if (isMouseOverButton(mousePosition))
	{
		state = ButtonState::hover;
	}
	else
	{
		state = ButtonState::idle;
	}
	updateColorByButtonState();
}

bool TextButton::wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (isMouseOverButton(mousePosition) && wasMouseLeftButtonPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void TextButton::updateColorByButtonState()
{
	switch (state)
	{
	case ButtonState::idle:
		shape.setFillColor(IdleColor);
		break;
	case ButtonState::hover:
		shape.setFillColor(HoverColor);
		break;
	}
}


bool TextButton::isMouseOverButton(const sf::Vector2f& mousePosition) const
{
	if (shape.getGlobalBounds().contains(mousePosition))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}

