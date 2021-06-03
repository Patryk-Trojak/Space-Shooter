#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "MenuState.h"

class Game
{
public:
	Game();
	virtual ~Game();
	void run();

private:
	std::stack < std::unique_ptr< State > > states;
	TexturesHolder textures;
	sf::Font font;
	sf::RenderWindow window;
	sf::Clock deltaTimeClock;
	sf::Event event;
	float deltaTime;
	bool closeWindow;
	void render();
	void update();
	void updateSFMLEvents();
	void updateDeltaTime();
	void popStates(int numberOfStates);


	void loadAllTextures();
};

