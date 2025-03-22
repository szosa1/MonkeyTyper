#ifndef PROJEKT_PJC_WORD_H
#define PROJEKT_PJC_WORD_H


#include <SFML/Graphics.hpp>
#include <string>
#include "Settings.h"

class Word : public sf::Drawable {
public:
    Word(const std::string& text, const sf::Font& font, int screenWidth, int screenHeight, Settings* settings);

    void update(sf::Time deltaTime); // aktualizuje pozycje wyrazu
    bool isOffScreen() const;
    std::string getText() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // rysuje wyraz  (!nadpisuje drawable)


private:


    sf::Text Text;
    int Speed;
    Settings* Settings;
};

#endif //PROJEKT_PJC_WORD_H
