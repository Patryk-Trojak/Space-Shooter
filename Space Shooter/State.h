#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "ResourceHolder.h"
#include "TexturesID.h"



class State
	:public sf::Drawable
{
public:
	State(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font);
	virtual ~State();
	virtual void update(const float deltaTime) = 0;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) = 0;
	void updateMousePositions(sf::RenderWindow& window);
	const sf::View& getView() const;
	const sf::View& getHUDView() const;
	bool getCloseWindow();
	int getNumberOfStatesPop() const;

protected:
	std::stack < std::unique_ptr< State > >& states;
	const ResourceHolder<TextureID, sf::Texture>& textures;
	const sf::Font& font;
	sf::Vector2f mousePositionView;
	sf::Vector2f mousePositionHUD;
	sf::Vector2f mousePositionWindow;
	sf::Sprite background;
	sf::View view;
	sf::View HUDView;
	bool closeWindow;
	int numberOfStatesPop;
	bool wasMousePressed;
	bool wasEscapePressed;
};

