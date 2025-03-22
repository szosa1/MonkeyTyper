#include "Game.h"
#include "Word.h"
#include <iostream>
#include <iomanip>

Game::Game()
        : Window(sf::VideoMode(screenWidth, screenHeight), "Monkey Typer Game")
        , MissedWords(0)
        , MainMenuScreen(Font, screenWidth, screenHeight)
        , SettingsScreen(Font, screenWidth, screenHeight)
        , HighscoresScreen(Font, screenWidth, screenHeight)
        , WordsSpawned(0)
        , bsCount(0)
{
    Font.loadFromFile("assets/PixelifySans-Regular.ttf");


    InputText.setFont(Font);
    InputText.setCharacterSize(24);
    InputText.setFillColor(sf::Color::White);
    InputText.setPosition(10, screenHeight- 40);

    NameInputText.setFont(Font);
    NameInputText.setCharacterSize(24);
    NameInputText.setFillColor(sf::Color::White);
    NameInputText.setPosition(10, screenHeight - 70);

    loadWordsFromFile("assets/words.txt");

    std::srand(static_cast<unsigned>(std::time(nullptr))); // do losowanie slow

    TimerText.setFont(Font);
    TimerText.setCharacterSize(20);
    TimerText.setPosition(screenWidth- 150, screenHeight - 50);

    ScoreText.setFont(Font);
    ScoreText.setCharacterSize(20);
    ScoreText.setPosition(screenWidth - 150, screenHeight - 100);

    MissedWordsText.setFont(Font);
    MissedWordsText.setCharacterSize(20);
    MissedWordsText.setPosition(screenWidth - 430, screenHeight - 100);
    updateMissedWordsText();

    InfoText.setString("Press BackSpace to start typing");
    InfoText.setFont(Font);
    InfoText.setCharacterSize(20);
    InfoText.setPosition(10, screenHeight- 40);

    GameClock.restart();
    spawnWord();

}

void Game::loadWordsFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open " << filePath << std::endl;
        exit(1);
    }

    std::string word;
    while (file >> word) {
        WordList.push_back(word);
    }
}

void Game::run() {
    sf::Clock clock;
    while (Window.isOpen()) {
        sf::Time frameTime = clock.restart(); // mierzy czas miedzy klatkami - zwraca frameTime czyli czas od poprzedniego clock.restart
        processEvents();

        if (MainMenuScreen.isStartScreenActive()){
            MainMenuScreen.draw(Window);
            render();
        }
        else if (SettingsScreen.isSettingsScreenActive()){
            SettingsScreen.draw(Window);       //rysuje settings
        }
        else if(HighscoresScreen.isHighscoresScreenActive()){
            HighscoresScreen.draw(Window);  //rysuje highscores
        }
        else{
            update(frameTime);          //ekran gra
            render();
        }
    }
}

void Game::processEvents() { //obsluga zdarzen: klawiatura okno itd
    sf::Event event;
    while (Window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) Window.close(); //zamyka po klikniecu na x

        if(MainMenuScreen.isStartScreenActive()){
            GameClock.restart();

            MainMenuScreen.handleEvent(event, Window);  //  eventy dla main menu

            if(MainMenuScreen.isSettingsSelected()){
                MainMenuScreen.deactivateStartScreen();
                SettingsScreen.activateSettingsScreen();
                IsPaused = true;
            }

            if(MainMenuScreen.isHighscoresSelected()){
                MainMenuScreen.deactivateStartScreen();
                HighscoresScreen.activateHighscoresScreen();
                IsPaused = true;
            }

            //obsluga wprowadzenia nazwy gracza
            if (MainMenuScreen.isEnterNameActive()) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            if (!PlayerName.empty()) {
                                PlayerName.pop_back();
                            }
                        } else if (event.text.unicode != 13) { // Sprawdzenie czy to enter
                            PlayerName += static_cast<char>(event.text.unicode);
                        }
                        MainMenuScreen.setPlayerNameText(PlayerName);
                    }
                }
            }

        }else if (SettingsScreen.isSettingsScreenActive()){

            SettingsScreen.handleEvent(event, Window); //eventy dla settings
            GameClock.restart();

            if(SettingsScreen.isExitSettingsScreen()){
                SettingsScreen.deactivateSettingsScreen();
                MainMenuScreen.activateStartScreen();
                SettingsScreen.resetExitFlag();
                MainMenuScreen.resetSettingsSelected();
                IsPaused = false;
            }

        }else if(HighscoresScreen.isHighscoresScreenActive()){

            HighscoresScreen.handleEvent(event, Window);
            GameClock.restart();

            if(HighscoresScreen.isExitHighscoreScreen()){
                HighscoresScreen.deactivateHighscoresScreen();
                MainMenuScreen.activateStartScreen();
                HighscoresScreen.resetExitFlag();
                MainMenuScreen.resetHighscoresSeleceted();
                IsPaused = false;
            }

        }else {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != 8) { // 8 - backspace
                    Input += static_cast<char>(event.text.unicode);
                    if(!MainMenuScreen.isStartScreenActive()){
                        checkInput();
                    }
                    InputText.setString(Input);
                }
            }
            if (event.type == sf::Event::KeyPressed){
                handleBackSpace(event.key.code, true); //wcisniece backspace
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if(IsPaused) return;

    if(!MainMenuScreen.isStartScreenActive()){
        for (auto& word : Words) { // aktualizuje pozycje slow
            word.update(deltaTime);
        }

        // usuwa wyrazy ktore wyszly poza ekran
        auto new_end = std::remove_if(Words.begin(), Words.end(), [this](Word& word) {
            if (word.isOffScreen()) {
                MissedWords++;
                updateMissedWordsText();
                return true;
            }
            return false;
        });
        Words.erase(new_end, Words.end());


        if (MissedWords >= MaxMissedWords) { //konczy gre jak za duzo przegapie
            saveHighscore(Score);
            HighscoresScreen.loadHighscoresFromFile("assets/highscores.txt");

            MissedWords = 0;
            updateMissedWordsText();

            Words.clear();
            Score = 0;
            bsCount = 0;
            MainMenuScreen.activateStartScreen();
        }

        // spawnuje nowe wyrazy
        static sf::Time timeSinceLastSpawn = sf::Time::Zero;
        timeSinceLastSpawn += deltaTime;
        if (timeSinceLastSpawn > sf::seconds(SettingsScreen.getFrequency())) {
            spawnWord();
            timeSinceLastSpawn = sf::Time::Zero;
        }


        updateTimerText();
        updateScore();


    }
}

void Game::render() { //rysowanie na ekranie
    Window.clear();

    //sprawdza ktory ekran jest aktywny i rysuje odpowiednio
    if (MainMenuScreen.isStartScreenActive()) {
        MainMenuScreen.draw(Window);

        if (MainMenuScreen.isEnterNameActive()) {
            Window.draw(MainMenuScreen.getPlayerNameText());
        }

    } else if (SettingsScreen.isSettingsScreenActive()) {
        SettingsScreen.draw(Window);

    } else if (HighscoresScreen.isHighscoresScreenActive()) {
        HighscoresScreen.draw(Window);

    } else {
        Window.draw(InputText);
        Window.draw(TimerText);
        Window.draw(ScoreText);
        Window.draw(MissedWordsText);

        if (bsCount == 0) {
            Window.draw(InfoText);
        }

        for (const auto& word : Words) {
            Window.draw(word);
        }
    }

    Window.display();
}

//usuwa znak po nacisnieciu BackSpace
void Game::handleBackSpace(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::BackSpace && isPressed && !Input.empty()) {
        Input.pop_back();
        InputText.setString(Input); // Aktualizuje Input
        bsCount++;
    }
}

//tworzy nowe slowo i dodaje je do listy slow
void Game::spawnWord() {
    WordsSpawned++;
    int random = std::rand()%WordList.size();
    std::string wordText = WordList[random];
    Words.push_back(Word(wordText, SettingsScreen.getFont(),screenWidth, screenHeight, &SettingsScreen));
}

//sprawdza czy aktualnie wpiane slowo jest w liscie slow
void Game::checkInput() {
    auto it = std::find_if(Words.begin(), Words.end(), [this](Word& word) { // lambda sprawdza czy slowo wpisane = slowo na liscie
        return word.getText() == Input;
    });

    if (it != Words.end()) {
        Score += Input.size();
        Words.erase(it);
        Input.clear();
    }
}

//aktualizuje timer
void Game::updateTimerText(){
    sf::Time elapsedTime = GameClock.getElapsedTime(); // czas ktory uplynal od uruchomienia zegara
    //std::cout<<WordsSpawned;
    float seconds = elapsedTime.asSeconds();
    std::ostringstream stringStream;
    stringStream << std::fixed << std::setprecision(1) <<"Time: "<< seconds << "s"; // jendo miejsce po przecinku

    TimerText.setString(stringStream.str());
}

//aktualizuje wynik
void Game::updateScore() {
    ScoreText.setString("Score: " + std::to_string(Score));
}

// aktualizuije pominiete slowa
void Game::updateMissedWordsText() {
    MissedWordsText.setString("Missed words: " + std::to_string(MissedWords));
}

void Game::saveHighscore(int score) {
    file.open("assets/highscores.txt", std::ios::app); // Otwórz plik do dopisywania (append)

    std::string word1 = PlayerName;
    std::string word2 = std::to_string(score);

    if (file.is_open()) {
        file << word1 << "\t" <<"\t"<< word2 << std::endl;
    } else {
        std::cout << "Unable to open highscores.txt for saving." << std::endl;
    }
    file.close();
}

