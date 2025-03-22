#include "Settings.h"

Settings::Settings(const sf::Font& font, int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{

    Font.loadFromFile("D:/Projekt PJC/assets/PixelifySans-Regular.ttf");

    loadFontsList();

    SettingsTitleText.setString("SETTINGS");
    SettingsTitleText.setFont(font);
    SettingsTitleText.setCharacterSize(36);
    SettingsTitleText.setPosition(screenWidth - 670, screenHeight- 780);


    SpeedLabel.setString("Word Speed:");
    SpeedLabel.setFont(font);
    SpeedLabel.setCharacterSize(25);
    SpeedLabel.setPosition(screenWidth - 750, screenHeight - 590);

    SpeedValue.setString(std::to_string(Speed));
    SpeedValue.setFont(font);
    SpeedValue.setCharacterSize(25);
    SpeedValue.setPosition(screenWidth - 532, screenHeight - 590);

    DecreaseSpeedButton.setString("<");
    DecreaseSpeedButton.setFont(font);
    DecreaseSpeedButton.setCharacterSize(25);
    DecreaseSpeedButton.setPosition(screenWidth - 560, screenHeight - 590);

    IncreaseSpeedButton.setString(">");
    IncreaseSpeedButton.setFont(font);
    IncreaseSpeedButton.setCharacterSize(25);
    IncreaseSpeedButton.setPosition(screenWidth - 490, screenHeight - 590);


    SpawnFrequency.setString("Word spawn frequency: \n(time between each word spawned)");
    SpawnFrequency.setFont(font);
    SpawnFrequency.setCharacterSize(25);
    SpawnFrequency.setPosition(screenWidth - 850, screenHeight - 490);

    FrequencyLabel.setString(std::to_string(Frequency));
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << Frequency; // zamiana na jedno miejsce po przecinku
    FrequencyLabel.setString(ss.str() + "s");
    FrequencyLabel.setFont(font);
    FrequencyLabel.setCharacterSize(25);
    FrequencyLabel.setPosition(screenWidth - 495, screenHeight - 490);

    DecreaseFrequencyButton.setString("<");
    DecreaseFrequencyButton.setFont(font);
    DecreaseFrequencyButton.setCharacterSize(25);
    DecreaseFrequencyButton.setPosition(screenWidth - 520, screenHeight - 490);

    IncreaseFrequencyButton.setString(">");
    IncreaseFrequencyButton.setFont(font);
    IncreaseFrequencyButton.setCharacterSize(25);
    IncreaseFrequencyButton.setPosition(screenWidth - 445, screenHeight - 490);


    ChangeFont.setString("Word font: ");
    ChangeFont.setFont(font);
    ChangeFont.setCharacterSize(25);
    ChangeFont.setPosition(screenWidth - 750, screenHeight - 390);

    FontLabel.setString(FontsList[count]); //to do
    FontLabel.setFont(font);
    FontLabel.setCharacterSize(25);
    FontLabel.setPosition(screenWidth - 540, screenHeight - 390);

    FontLeft.setString("<");
    FontLeft.setFont(font);
    FontLeft.setCharacterSize(25);
    FontLeft.setPosition(screenWidth - 575, screenHeight - 390);

    FontRight.setString(">");
    FontRight.setFont(font);
    FontRight.setCharacterSize(25);
    FontRight.setPosition(screenWidth - 440, screenHeight - 390);


    ExitButton.setString("Exit");
    ExitButton.setFont(font);
    ExitButton.setCharacterSize(36);
    ExitButton.setPosition(screenWidth - 1190, screenHeight- 790);
    updateFontLabelPosition();

}

void Settings::draw(sf::RenderWindow& window) { //rysuje wszystkie elementy ekranu
    window.clear();
    updateFontLabelPosition(); // zmienia ustawienie > jeszcze przed naryswaniem w zaleznosci od dlugosci napisu
    window.draw(SettingsTitleText);
    window.draw(ExitButton);
    window.draw(SpeedLabel);
    window.draw(SpeedValue);
    window.draw(DecreaseSpeedButton);
    window.draw(IncreaseSpeedButton);
    window.draw(SpawnFrequency);
    window.draw(FrequencyLabel);
    window.draw(DecreaseFrequencyButton);
    window.draw(IncreaseFrequencyButton);
    window.draw(ChangeFont);
    window.draw(FontLabel);
    window.draw(FontLeft);
    window.draw(FontRight);

    window.display();
}

void Settings::handleEvent(const sf::Event& event, sf::RenderWindow& window) {

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // pobiera pozycje kursora
    sf::FloatRect ExitButtonBounds = ExitButton.getGlobalBounds();
    sf::FloatRect DecreaseSpeedBounds = DecreaseSpeedButton.getGlobalBounds();
    sf::FloatRect IncreaseSpeedBounds = IncreaseSpeedButton.getGlobalBounds();
    sf::FloatRect DecreaseFrequencyBounds = DecreaseFrequencyButton.getGlobalBounds();
    sf::FloatRect IncreaseFrequencyBounds = IncreaseFrequencyButton.getGlobalBounds();
    sf::FloatRect FontLeftBounds = FontLeft.getGlobalBounds();
    sf::FloatRect FontRightBounds = FontRight.getGlobalBounds();

    if(ExitButtonBounds.contains(mousePosition.x, mousePosition.y)){
        ExitButton.setFillColor(sf::Color::Red);
    }else{
        ExitButton.setFillColor(sf::Color::White);
    }

    if(DecreaseSpeedBounds.contains(mousePosition.x, mousePosition.y)){
        DecreaseSpeedButton.setFillColor(sf::Color::Red);
    } else {
        DecreaseSpeedButton.setFillColor(sf::Color::White);
    }

    if(IncreaseSpeedBounds.contains(mousePosition.x, mousePosition.y)){
        IncreaseSpeedButton.setFillColor(sf::Color::Red);
    }else{
        IncreaseSpeedButton.setFillColor(sf::Color::White);
    }

    if(DecreaseFrequencyBounds.contains(mousePosition.x, mousePosition.y)){
        DecreaseFrequencyButton.setFillColor(sf::Color::Red);
    }else{
        DecreaseFrequencyButton.setFillColor(sf::Color::White);
    }

    if(IncreaseFrequencyBounds.contains(mousePosition.x, mousePosition.y)){
        IncreaseFrequencyButton.setFillColor(sf::Color::Red);
    }else{
        IncreaseFrequencyButton.setFillColor(sf::Color::White);
    }

    if(FontLeftBounds.contains(mousePosition.x, mousePosition.y)){
        FontLeft.setFillColor(sf::Color::Red);
    }else{
        FontLeft.setFillColor(sf::Color::White);
    }

    if(FontRightBounds.contains(mousePosition.x, mousePosition.y)){
        FontRight.setFillColor(sf::Color::Red);
    }else{
        FontRight.setFillColor(sf::Color::White);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        if(ExitButtonBounds.contains(mousePosition.x, mousePosition.y)){
            deactivateSettingsScreen();
            exitSettingsScreen();
        }

        if(DecreaseSpeedBounds.contains(mousePosition.x, mousePosition.y)){
            if (Speed > 10) {
                Speed -= 10;
                SpeedValue.setString(std::to_string(Speed));
            }
        }

        if(IncreaseSpeedBounds.contains(mousePosition.x, mousePosition.y)) {
            Speed += 10;
            SpeedValue.setString(std::to_string(Speed));
        }

        if(DecreaseFrequencyBounds.contains(mousePosition.x, mousePosition.y)){
            if(Frequency > 0.1f){
                Frequency -= 0.1;
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(1) << Frequency; // zamiana na 1 miejsce po przecinku
                FrequencyLabel.setString(ss.str() + "s");
            }
        }

        if(IncreaseFrequencyBounds.contains(mousePosition.x, mousePosition.y)){
            Frequency += 0.1;
            FrequencyLabel.setString(std::to_string(Frequency));
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(1) << Frequency; // zamiana na 1 miejsce po przecinku
            FrequencyLabel.setString(ss.str() + "s");

        }

        if(FontLeftBounds.contains(mousePosition.x, mousePosition.y)){
            if(count > 0){
                count--;
                FontLabel.setString(FontsList[count]);
                updateFontLabelPosition();
            }else if(count == 0){
                count = FontsList.size()- 1;
                FontLabel.setString(FontsList[count]);
                updateFontLabelPosition();
            }

        }

        if(FontRightBounds.contains(mousePosition.x, mousePosition.y)){
            if(count < FontsList.size() -1){
                count++;
                FontLabel.setString(FontsList[count]);
                updateFontLabelPosition();
            } else if(count == FontsList.size() -1 ){
                count = 0;
                FontLabel.setString(FontsList[count]);
                updateFontLabelPosition();
            }
        }
    }

    if(count == 0){
        if (!Font.loadFromFile("assets/Arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }
    }else if(count == 1){
        if (!Font.loadFromFile("assets/PixelifySans-Regular.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }
    }else if(count == 2){
        if (!Font.loadFromFile("assets/Ldfcomicsansbold-zgma.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }
    }else if(count == 3){
        if (!Font.loadFromFile("assets/GreatVibes-Regular.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }
    }

}

bool Settings::isSettingsScreenActive() const {
    return IsSettingsScreen;
}

void Settings::deactivateSettingsScreen() {
    IsSettingsScreen = false;
}

void Settings::activateSettingsScreen() {
    IsSettingsScreen = true;
}

bool Settings::isExitSettingsScreen() const {
    return IsExit;
}

void Settings::exitSettingsScreen() {
    IsExit = true;
}

void Settings::resetExitFlag() {
    IsExit = false;
}

int Settings::getSpeed() const {
    return Speed;
}

float Settings::getFrequency() const {
    return Frequency;
}


void Settings::loadFontsList() {
    FontsList.push_back("Arial"); // 0
    FontsList.push_back("Pixelify"); // 1
    FontsList.push_back("ComicSans"); // 2
    FontsList.push_back("Cursive"); // 3
}

const sf::Font& Settings::getFont() const {
    return Font;
}

void Settings::updateFontLabelPosition() {
    sf::FloatRect fontLabelBounds = FontLabel.getGlobalBounds();

    FontLeft.setPosition(FontLabel.getPosition().x - 30, FontLabel.getPosition().y);
    FontRight.setPosition( FontLabel.getPosition().x  + fontLabelBounds.width+ 18, FontLabel.getPosition().y);
}