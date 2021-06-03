#include "InfoState.h"

InfoState::InfoState(std::stack<std::unique_ptr<State>>& states, const TexturesHolder& textures, const sf::Font& font)
    :State(states, textures, font)
{
    const std::wstring message = L"Gra stworzona przez Patryka Trojaka z Liceum Ogólnokszta³c¹cego im. Adama Mickiewicza w Górze na\nXXI Ogólnopolski Górowski Konkurs Informatyczny klas VII i VIII szkó³ podstawowych i uczniów \nszkó³ ponadpodstawowych w roku szkolnym 2020/2021. \nDo jej stworzenia zosta³ u¿yty c++ oraz biblioteka SFML (https://www.sfml-dev.org).\n\nInformacje o rozgrywce:\nZasady: W grze musimy walczyæ z asteroidami.\nGramy dopóki gracz bêdzie mia³ 0 punktów zdrowia(zdrowie traci poprzez kolizjê z asteroidami) \nlub asteroida nie spadnie poza ekran.\nSterowanie :\nStrza³ - lewy przycisk myszy.\nStatkiem porusza siê za pomoc¹ kursora.";
    info.setPosition(40, 100);
    info.setFont(font);
    info.setString(message);
    info.setCharacterSize(55);
    info.setFillColor(sf::Color::White);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(2.f);
}

InfoState::~InfoState()
{
}

void InfoState::update(const float deltaTime)
{
}

void InfoState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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

void InfoState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(info);
}
