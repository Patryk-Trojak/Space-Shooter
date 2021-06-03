#include "MenuState.h"

MenuState::MenuState(std::stack<std::unique_ptr<State>>& states, const TexturesHolder& textures, const sf::Font& font)
    :State(states, textures, font)
{
    initButtons();
}

void MenuState::update(const float deltaTime)
{
    updateButtons();
    handleFunctionalityOfButtons();
}

void MenuState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
            }
        }
    }
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background);
    drawAllButtons(target);
}

void MenuState::initButtons()
{
    buttons.emplace(std::make_pair(ButtonName::GoToGameplayState, 
                                    TextButton(sf::Vector2f((1920.f - 300.f) / 2.f, 400.f), sf::Vector2f(300.f, 70.f), textures.getResource(TextureID::greyButton), font, L"GRAJ", 45))); 

    buttons.emplace(std::make_pair(ButtonName::GoToInfoState,
                                    TextButton(sf::Vector2f((1920.f - 300.f) / 2.f, 500.f), sf::Vector2f(300.f, 70.f), textures.getResource(TextureID::greyButton), font, L"INFORMACJE", 45)));
    
    buttons.emplace(std::make_pair(ButtonName::ExitGame,
                                    TextButton(sf::Vector2f((1920.f - 300.f) / 2.f, 600.f), sf::Vector2f(300.f, 70.f), textures.getResource(TextureID::greyButton), font, L"WYJDè", 45)));
}

void MenuState::updateButtons()
{
    for (auto& i : buttons)
        i.second.update(mousePositionView);
}

void MenuState::handleFunctionalityOfButtons()
{
    for (auto& i : buttons)
    {
        if (i.second.wasPressed(mousePositionView, wasMousePressed))
        {
            switch (i.first)
            {
            case ButtonName::GoToGameplayState:
                states.emplace(std::make_unique< GameplayState >(states, textures, font));
                break;
            case ButtonName::GoToInfoState:
                states.emplace(std::make_unique< InfoState >(states, textures, font));
                break;
            case ButtonName::ExitGame:
                closeWindow = true;
                break;
            default:
                break;
            }
        }
    }
}

void MenuState::drawAllButtons(sf::RenderTarget& target) const
{
    for (auto const& i : buttons)
    {
        target.draw(i.second);
    }
}
