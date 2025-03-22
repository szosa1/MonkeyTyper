#include <iostream>
#include <fstream>
#include "Highscores.h"

Highscores::Highscores(const sf::Font& font, int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight), Font(font)
{
    Font.loadFromFile("assets/PixelifySans-Regular.ttf");

    HighscoresTitleText.setString("HIGHSCORES");
    HighscoresTitleText.setFont(Font);
    HighscoresTitleText.setCharacterSize(36);
    HighscoresTitleText.setPosition(screenWidth / 2 - 100, 50);

    ExitButton.setString("Exit");
    ExitButton.setFont(Font);
    ExitButton.setCharacterSize(36);
    ExitButton.setPosition(screenWidth - 100, screenHeight - 100);

    loadHighscoresFromFile("assets/highscores.txt");
}

void Highscores::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(HighscoresTitleText);
    window.draw(ExitButton);

    for (const auto& scoreText : ScoreTexts) {
        window.draw(scoreText);
    }

    window.display();
}

void Highscores::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect ExitButtonBounds = ExitButton.getGlobalBounds();

    if(ExitButtonBounds.contains(mousePosition.x, mousePosition.y)){
        ExitButton.setFillColor(sf::Color::Red);
    }else{
        ExitButton.setFillColor(sf::Color::White);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (ExitButtonBounds.contains(mousePosition.x, mousePosition.y)) {
            deactivateHighscoresScreen();
            exitHighcores();
        }
    }
}

bool Highscores::isHighscoresScreenActive() const {
    return IsHighscoresScreen;
}

void Highscores::activateHighscoresScreen() {
    IsHighscoresScreen = true;
}

void Highscores::deactivateHighscoresScreen() {
    IsHighscoresScreen = false;
}

bool Highscores::isExitHighscoreScreen() {
    return IsExit;
}

void Highscores::exitHighcores() {
    IsExit = true;
}

void Highscores::resetExitFlag() {
    IsExit = false;
}


void Highscores::loadHighscoresFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file) {
        std::cerr << "Failed to open " << filePath << std::endl;
        return;
    }

    std::string line;
    int yOffset = 150;
    int xPos = 190;
    while (std::getline(file, line)) {

        if(yOffset > 700){
            xPos += 300;
            yOffset = 150;
        }

        sf::Text scoreText;
        scoreText.setFont(Font);
        scoreText.setCharacterSize(24);
        scoreText.setString(line);
        scoreText.setPosition(xPos, yOffset);
        yOffset += 30; // odleglosc miedzy liniami
        ScoreTexts.push_back(scoreText);
    }
}