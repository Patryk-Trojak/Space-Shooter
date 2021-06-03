#pragma once
#include <unordered_map>
#include <iostream>
#include "State.h"
#include "TextButton.h"
#include "GameplayState.h"
#include "InfoState.h"

enum class ButtonName {
	GoToGameplayState,
	GoToInfoState,
	ExitGame
};

class MenuState
	:public State
{
public:
	MenuState(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font);
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::unordered_map<ButtonName, TextButton> buttons;

	void initButtons();
	void updateButtons(); 
	void handleFunctionalityOfButtons();
	void drawAllButtons(sf::RenderTarget& target) const;
};

