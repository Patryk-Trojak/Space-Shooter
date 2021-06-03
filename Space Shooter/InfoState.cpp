#include "InfoState.h"

InfoState::InfoState(std::stack<std::unique_ptr<State>>& states, const TexturesHolder& textures, const sf::Font& font)
    :State(states, textures, font)
{
    const std::wstring message = L"Gra stworzona przez Patryka Trojaka z Liceum Og�lnokszta�c�cego im. Adama Mickiewicza w G�rze na\nXXI Og�lnopolski G�rowski Konkurs Informatyczny klas VII i VIII szk� podstawowych i uczni�w \nszk� ponadpodstawowych w roku szkolnym 2020/2021. \nDo jej stworzenia zosta� u�yty c++ oraz biblioteka SFML (https://www.sfml-dev.org).\n\nInformacje o rozgrywce:\nZasady: W grze musimy walczy� z asteroidami.\nGramy dop�ki gracz b�dzie mia� 0 punkt�w zdrowia(zdrowie traci poprzez kolizj� z asteroidami) \nlub asteroida nie spadnie poza ekran.\nSterowanie :\nStrza� - lewy przycisk myszy.\nStatkiem porusza si� za pomoc� kursora.";
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
