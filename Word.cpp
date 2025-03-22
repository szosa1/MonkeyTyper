#include "Word.h"

Word::Word(const std::string& text, const sf::Font& font, int screenWidth, int screenHeight, class Settings* settings)
        : Settings(settings)
{
    Speed = Settings->getSpeed();

    Text.setFont(font);
    Text.setString(text);
    Text.setCharacterSize(24);
    Text.setFillColor(sf::Color::White);
    Text.setPosition(screenWidth, rand() % (screenHeight-200));

}

void Word::update(sf::Time deltaTime) { //przesuwa tekst w lewo
    float movement = Speed * deltaTime.asSeconds();
    Text.move(-movement, 0);
}

bool Word::isOffScreen() const { // sprawdza czy wyszedl poza ekran
    return Text.getPosition().x + Text.getGlobalBounds().width < 0;
}

std::string Word::getText() const { //aktualny tekst wyrazu
    return Text.getString();
}

void Word::draw(sf::RenderTarget& target, sf::RenderStates states) const { // rysuje wyraz na ekranie
    target.draw(Text, states);
}



