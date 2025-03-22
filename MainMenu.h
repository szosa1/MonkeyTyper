#ifndef PROJEKT_PJC_MAINMENU_H
#define PROJEKT_PJC_MAINMENU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Settings.h"


class MainMenu{
public:
    MainMenu(const sf::Font& font, int screenWidth, int screenHeight);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    bool isStartScreenActive() const;
    void activateStartScreen();
    void deactivateStartScreen();


    bool isSettingsSelected() const;
    void resetSettingsSelected();

    bool isHighscoresSelected() const;
    void resetHighscoresSeleceted();


    bool isEnterNameActive() const;
    void activateEnterName();
    void deactivateEnterName();

    const sf::Text& getPlayerNameText() const;

    void setPlayerNameText(const std::string& text);





private:
    sf::Text NewGameText;
    sf::Text SettingsText;
    sf::Text HighScoreText;
    sf::Text ExitGameText;
    sf::Text EnterNameText;
    sf::Text NameInputText;
    std::string PlayerName;
    sf::Text PlayerNameText;

    bool IsStartScreen = true;
    bool IsSettingsSelected = false;
    bool IsHighscoresSelected = false;
    bool EnterNameActive = false;

};

#endif
