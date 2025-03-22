#ifndef PROJEKT_PJC_SETTINGS_H
#define PROJEKT_PJC_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <vector>


class Settings {
public:
    Settings(const sf::Font& font, int screenWidth, int screenHeight);

    void draw(sf::RenderWindow& settingsWindow);
    void handleEvent(const sf::Event& event, sf::RenderWindow& Window);

    bool isSettingsScreenActive() const;
    void deactivateSettingsScreen();
    void activateSettingsScreen();

    bool isExitSettingsScreen() const;
    void exitSettingsScreen();
    void resetExitFlag();

    int getSpeed() const;

    float getFrequency() const;

    const sf::Font& getFont() const;

private:
    int screenWidth;
    int screenHeight;

    sf::Text SettingsTitleText;
    sf::Text ExitButton;

    sf::Text SpeedLabel;
    sf::Text SpeedValue;
    sf::Text DecreaseSpeedButton;
    sf::Text IncreaseSpeedButton;

    sf::Text SpawnFrequency;
    sf::Text FrequencyLabel;
    sf::Text DecreaseFrequencyButton;
    sf::Text IncreaseFrequencyButton;

    sf::Text ChangeFont;
    sf::Text FontLabel;
    sf::Text FontLeft;
    sf::Text FontRight;
    std::vector<std::string> FontsList;
    sf::Font Font;

    std::string EnteredSpeed;

    void loadFontsList();
    void updateFontLabelPosition();

    bool IsSettingsScreen = false;
    bool IsExit = false;
    int Speed = 80;
    float Frequency = 1;
    int count = 0;
};

#endif //PROJEKT_PJC_SETTINGS_H
