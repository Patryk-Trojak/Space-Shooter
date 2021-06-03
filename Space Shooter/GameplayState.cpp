#include "GameplayState.h"

GameplayState::GameplayState(std::stack < std::unique_ptr< State > >& states, const TexturesHolder& textures, const sf::Font& font)
	:State(states, textures, font),
    player(mousePositionView, textures.getResource(TextureID::spaceship), textures.getResource(TextureID::projectile)),
    timerOfCreatingEnemies(0.f),
    collisionsHandler(player, projectiles, enemies, upgrades, particleSystem, textures),
    playerHUD(textures, font),
    timerBetweenWaves(0.f),
    numberOfWave(1),
    maxNumberOfEnemiesInWave(0),
    numberOfSpawnedEnemiesInWave(0),
    isWave(false),
    timeBetweenSpawningEnemies(0),
    infoAboutLost(L"Przegra³eœ!\nKliknij escape aby wróciæ do menu", font, 70)
{
    infoAboutLost.setPosition({ 600.f, 450.f });
}

void GameplayState::update(const float deltaTime)
{
    if (!end)
    {
        player.update(mousePositionView);
        player.updateShooting(projectiles, deltaTime);
        updateProjectiles(deltaTime);
        handleCreatingEnemies(deltaTime);
        updateEnemies(deltaTime);
        updateUpgrades(deltaTime);
        particleSystem.update(deltaTime);

        collisionsHandler.projectilesAndEnemies();
        collisionsHandler.playerAndEnemies();
        collisionsHandler.playerAndUpgrades();
        eraseProjectileIfItOutOfScreen();

        playerHUD.update(player.getHp(), numberOfWave);
        tryEndGame();
    }   
}

void GameplayState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
    wasMousePressed = false;
    wasEscapePressed = false;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                wasMousePressed = true;
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                wasEscapePressed = true;
                numberOfStatesPop = 1;
            }
        }    
    }
}

void GameplayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(particleSystem);
    target.draw(player);
    for (auto& i : projectiles)
        target.draw(*i);
    for (auto& i : enemies)
        target.draw(*i);
    for (auto& i : upgrades)
        target.draw(*i);

    target.setView(HUDView);
    target.draw(playerHUD);

    target.setView(view);
 
    if(end)
    {
        target.draw(infoAboutLost);
    }  
}

void GameplayState::updateProjectiles(float deltaTime)
{
    for (auto& i : projectiles)
        i->update(deltaTime);
}

void GameplayState::updateEnemies(float deltaTime)
{
    for (auto& i : enemies)
        i->update(deltaTime);
}

void GameplayState::updateUpgrades(float deltaTime)
{
    for (auto& i : upgrades)
        i->update(deltaTime);
}

void GameplayState::handleCreatingEnemies(float deltaTime)
{
    if (!isWave)
    {
        timerBetweenWaves += deltaTime;
        if (timerBetweenWaves > 3.f)
        {
            isWave = true;

            numberOfSpawnedEnemiesInWave = 0;
            maxNumberOfEnemiesInWave = 10 + numberOfWave * 5;
            timerOfCreatingEnemies = 0;
            timeBetweenSpawningEnemies = 1.f - static_cast<float>(numberOfWave) * 0.08f;
        }         
    }
    else
    {
        timerOfCreatingEnemies += deltaTime;
        if (timerOfCreatingEnemies > timeBetweenSpawningEnemies)
        {
            enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(static_cast<float>(RandomEngine::randInt(0, 1920)), -50.f), sf::Vector2f(0, 200.f + numberOfWave * 80.f), 200.f + numberOfWave * 20.f, textures.getResource(TextureID::asteroids)));
            timerOfCreatingEnemies = 0.f;
            numberOfSpawnedEnemiesInWave++; 
        }

        if (numberOfSpawnedEnemiesInWave > maxNumberOfEnemiesInWave)
        {
            timerBetweenWaves = 0.f;
            isWave = false;
            numberOfWave++;
        }
        
    }
    
}

void GameplayState::eraseProjectileIfItOutOfScreen()
{
    auto it = projectiles.begin();
    while (!projectiles.empty())
    {
        bool isLastElement = false;
        if (it == projectiles.end() - 1)
            isLastElement = true;

        if ((*it)->getPosition().y + 50.f < 0.f)
        {
            *it = std::move(projectiles.back());
            projectiles.pop_back();
        }
        else
        {
            it++;
        }

        if (isLastElement)
            break;
    }
}

void GameplayState::tryEndGame()
{
    if (player.getHp() <= 0)
        end = true;
    if (isEnemyUnderTheScreen())
        end = true;
}

bool GameplayState::isEnemyUnderTheScreen()
{
    for (auto const& i : enemies)
    {
        if (i->getPosition().y + i->getRadius() > 1100)
            return true;
    }

    return false;
}
