#pragma once
#include <iostream>
#include "State.h"
#include "TextButton.h"
#include "GameplayState.h"


class InfoState
	:public State
{
public:
	InfoState(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font);
	virtual ~InfoState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text info;
};

