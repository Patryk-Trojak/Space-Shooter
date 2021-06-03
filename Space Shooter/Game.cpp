#include "Game.h"


Game::Game()
{
	window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Dungeon Plunderers", sf::Style::Fullscreen);
	loadAllTextures();
	font.loadFromFile("orange kid.ttf");
	window.setPosition(sf::Vector2i(0, 0));
	states.emplace(std::make_unique< MenuState >(states, textures, font) );
	window.setFramerateLimit(200);
}


Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{
		if (states.top()->getCloseWindow())
			window.close();
		updateSFMLEvents();

		if (window.hasFocus())
		{
			updateDeltaTime();
			states.top()->updateMousePositions(window);

			if (deltaTime < 0.3f)
			{
				states.top()->update(deltaTime);
			}

			render();
			popStates(states.top()->getNumberOfStatesPop());
		}
	}
}

void Game::render()
{
	window.clear(sf::Color(20, 20, 20));
	window.draw(*states.top());
	window.display();
}

void Game::update()
{
	states.top()->update(deltaTime);
}

void Game::updateSFMLEvents()
{
	states.top()->handleSFMLEvent(window, event);
}

void Game::updateDeltaTime()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
}

void Game::popStates(int numberOfStates)
{
	for (int i = 0; i < numberOfStates; i++)
	{
		if (!states.empty())
			states.pop();
		else
			window.close();
	}
}

void Game::loadAllTextures()
{
	textures.load(TextureID::spaceship, ".\\Textures\\SpaceShip.png");
	textures.load(TextureID::asteroids, ".\\Textures\\Asteroid.png");
	textures.load(TextureID::projectile, ".\\Textures\\Projectile.png");
	textures.load(TextureID::healthBarBackground, ".\\Textures\\HealthBarBackground.png");
	textures.load(TextureID::healthBarValue, ".\\Textures\\HealthBarValue.png");
	textures.load(TextureID::greyButton, ".\\Textures\\GreyButton.png");
	textures.load(TextureID::upgrade, ".\\Textures\\Upgrade.png");

	std::unique_ptr<sf::Texture> textureOfBackground = std::make_unique<sf::Texture>();
	textureOfBackground->loadFromFile(".\\Textures\\Background.png");
	textureOfBackground->setRepeated(true);
	textures.add(TextureID::background, std::move(textureOfBackground));
}
