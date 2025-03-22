#include "MainMenu.h"
#include "Settings.h"

MainMenu::MainMenu(const sf::Font &font, int screenWidth, int screenHeight) {
    NewGameText.setString("New Game");
    NewGameText.setFont(font);
    NewGameText.setCharacterSize(36);
    NewGameText.setFillColor(sf::Color::White);
    NewGameText.setPosition(screenWidth - 690, screenHeight-600);


    SettingsText.setString("Settings");
    SettingsText.setFont(font);
    SettingsText.setCharacterSize(36);
    SettingsText.setFillColor(sf::Color::White);
    SettingsText.setPosition(screenWidth - 680, screenHeight- 500);


    HighScoreText.setString("Highscores");
    HighScoreText.setFont(font);
    HighScoreText.setCharacterSize(36);
    HighScoreText.setFillColor(sf::Color::White);
    HighScoreText.setPosition(screenWidth - 695, screenHeight- 400);


    ExitGameText.setString("Exit Game");
    ExitGameText.setFont(font);
    ExitGameText.setCharacterSize(36);
    ExitGameText.setFillColor(sf::Color::White);
    ExitGameText.setPosition(screenWidth - 690, screenHeight-300);


    EnterNameText.setString("Enter your name:");
    EnterNameText.setFont(font);
    EnterNameText.setCharacterSize(24);
    EnterNameText.setPosition(screenWidth / 2 - 150, screenHeight / 2 + 50);

    PlayerNameText.setFont(font);
    PlayerNameText.setCharacterSize(24);
    PlayerNameText.setFillColor(sf::Color::White);
    PlayerNameText.setPosition(screenWidth / 2 - 150, screenHeight / 2 + 100);
}


void MainMenu::draw(sf::RenderWindow &window) {
    if(IsStartScreen){
        if(EnterNameActive){
            window.draw(EnterNameText);
            window.draw(NameInputText);
        }else{
            window.draw(NewGameText);
            window.draw(SettingsText);
            window.draw(HighScoreText);
            window.draw(ExitGameText);
        }
    }
}



void MainMenu::handleEvent(const sf::Event &event, sf::RenderWindow &window) {

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // pozycja myszki na ekranie
    sf::FloatRect newGameBounds = NewGameText.getGlobalBounds(); // biore wymiary tekstu 'new game'
    sf::FloatRect SettingsBounds = SettingsText.getGlobalBounds(); // itd reszta tak samo
    sf::FloatRect HighScoreBounds = HighScoreText.getGlobalBounds();
    sf::FloatRect ExitGameBounds = ExitGameText.getGlobalBounds();

    if(newGameBounds.contains(mousePosition.x, mousePosition.y)){
        NewGameText.setFillColor(sf::Color::Red);
    }else{
        NewGameText.setFillColor(sf::Color::White);
    }

    if(SettingsBounds.contains(mousePosition.x, mousePosition.y)){
        SettingsText.setFillColor(sf::Color::Red);
    }else{
        SettingsText.setFillColor(sf::Color::White);
    }

    if(HighScoreBounds.contains(mousePosition.x, mousePosition.y)){
        HighScoreText.setFillColor(sf::Color::Red);
    }else{
        HighScoreText.setFillColor(sf::Color::White);
    }

    if(ExitGameBounds.contains(mousePosition.x, mousePosition.y)){
        ExitGameText.setFillColor(sf::Color::Red);
    }else{
        ExitGameText.setFillColor(sf::Color::White);
    }

    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){ //kiedy lewy przycisk klikniety

        if(newGameBounds.contains((mousePosition.x), (mousePosition.y))){
            activateEnterName();
        }

        if(SettingsBounds.contains((mousePosition.x), (mousePosition.y))){
            deactivateStartScreen();
            IsSettingsSelected = true;
        }

        if(HighScoreBounds.contains((mousePosition.x), (mousePosition.y))){
            deactivateStartScreen();
            IsHighscoresSelected = true;
        }

        if (ExitGameBounds.contains((mousePosition.x), (mousePosition.y))) {
            window.close();
        }
    }

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
        if (EnterNameActive) {
            deactivateStartScreen();
            deactivateEnterName();
        }
    }
}

bool MainMenu::isStartScreenActive() const {
    return IsStartScreen;
}

void MainMenu::activateStartScreen() {
    IsStartScreen = true;
}

void MainMenu::deactivateStartScreen() {
    IsStartScreen = false;
}

bool MainMenu::isSettingsSelected() const {
    return IsSettingsSelected;
}

void MainMenu::resetSettingsSelected() {
    IsSettingsSelected = false;
}

bool MainMenu::isHighscoresSelected() const {
    return IsHighscoresSelected;
}

void MainMenu::resetHighscoresSeleceted() {
    IsHighscoresSelected = false;
}

bool MainMenu::isEnterNameActive() const {
    return EnterNameActive;
}

void MainMenu::activateEnterName() {
    EnterNameActive = true;
}

void MainMenu::deactivateEnterName() {
    EnterNameActive = false;
}

const sf::Text& MainMenu::getPlayerNameText() const {
    return PlayerNameText;
}

void MainMenu::setPlayerNameText(const std::string& text) {
    PlayerNameText.setString(text);
}



