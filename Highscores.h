#ifndef PROJEKT_PJC_HIGHSCORES_H
#define PROJEKT_PJC_HIGHSCORES_H

#include <SFML/Graphics.hpp>


class Highscores {
public:
    Highscores(const sf::Font& font, int screenWidth, int screenHeight);
    int screenWidth;
    int screenHeight;

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    bool isHighscoresScreenActive() const;
    void activateHighscoresScreen();
    void deactivateHighscoresScreen();

    bool isExitHighscoreScreen();
    void exitHighcores();
    void resetExitFlag();

    void loadHighscoresFromFile(const std::string& filePath);


private:

    sf::Text HighscoresTitleText;
    sf::Text ExitButton;
    std::vector<sf::Text> ScoreTexts;


    bool IsHighscoresScreen = false;
    bool IsExit = false;

    sf::Font Font;

};

#endif //PROJEKT_PJC_HIGHSCORES_H
