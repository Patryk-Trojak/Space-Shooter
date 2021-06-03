#include "State.h"


State::State(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font)
	:states(states),
	textures(textures),
	numberOfStatesPop(0),
	wasEscapePressed(false),
	wasMousePressed(false),
	font(font)
{         
	view.setSize(1920, 1080);
	view.setCenter(1920 / 2, 1080 / 2);
	HUDView = view;
	closeWindow = false;
	wasMousePressed = false;

	background.setTexture(textures.getResource(TextureID::background));
	background.setTextureRect(sf::IntRect(0, 0, 2300, 1400));
}

State::~State()
{
}

void State::updateMousePositions(sf::RenderWindow& window)
{
	window.setView(view);
	mousePositionView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	window.setView(HUDView);
	mousePositionHUD = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	window.setView(view);
}

const sf::View& State::getView() const
{
	return view;
}

const sf::View& State::getHUDView() const
{
	return HUDView;
}


bool State::getCloseWindow()
{
	return closeWindow;
}

int State::getNumberOfStatesPop() const
{
	return numberOfStatesPop;
}


