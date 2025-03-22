#ifndef PROJEKT_PJC_GAME_H
#define PROJEKT_PJC_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Settings.h"
#include "Word.h"
#include "MainMenu.h"
#include "Highscores.h"



class Game {
public:
    Game();
    void run();
    int screenWidth = 1200;
    int screenHeight = 800;

private:
    void loadWordsFromFile(const std::string& filePath);
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handleBackSpace(sf::Keyboard::Key, bool isPressed);
    void spawnWord();
    void checkInput();
    void updateTimerText();
    void updateScore();
    void updateMissedWordsText();
    void saveHighscore(int score);

    sf::RenderWindow Window;
    std::vector<Word> Words;
    sf::Font Font;

    std::string Input;

    int MissedWords;
    int Score =0;


    sf::Text InputText; // z klawiatury
    sf::Text TimerText; //zegar
    sf::Text ScoreText; //wynik
    sf::Text MissedWordsText; // przegapione slowa
    std::vector<std::string> WordList; // tablica slow ktore sie pojawiaja
    sf::Clock GameClock; // zegar
    sf::Text PlayerNameText;
    std::string PlayerName;
    sf::Text NameInputText;
    sf::Text InfoText; // info

    MainMenu MainMenuScreen;
    Settings SettingsScreen;
    Highscores HighscoresScreen;

    bool isSaved = false;
    bool shouldRender = false;
    bool IsStartScreen = true;
    sf::Text StartText;

    bool IsPaused = false; // to nie pauzuje gry, po prostu czas ma sie naliczac tylko w oknie game, a nie settings itd

    const int MaxMissedWords = 5;

    int WordsSpawned = 0;
    std::ofstream file;

    int bsCount = 0;
};

#endif
