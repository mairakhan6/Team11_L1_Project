#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "timer.hpp"
#include "player.hpp"
#include "boardTheme.hpp"
#include "welcome.hpp"
#include "inputBox.hpp"
#include "dropdown.hpp"

class Settings {
public:
    Settings();
    void display(sf::RenderWindow& window);

private:
    void settingScreen();
    void handleEvents(sf::RenderWindow& window);
    void openWelcome();
    void saveSettings();

    // next and back
    sf::Font font;
    sf::RectangleShape backButton, nextButton;
    sf::Text backText, nextText;

    // inputs (keyboard ones)
    sf::Text player1Label, player2Label, themeLabel, timerLabel, minsLabel, secsLabel;
    InputBox player1Input;
    InputBox player2Input;
    Dropdown themeDropdown;
    Dropdown timerMins;
    Dropdown timerSecs;

    // data for input storage
    std::string player1Name, player2Name;
    float timerLimit;
    bool timerSet;
    BoardTheme* boardTheme;
    Player player1, player2;
    Timer timer;
};

#endif 