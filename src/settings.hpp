#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.hpp"
#include "boardTheme.hpp"
#include "welcome.hpp"

class Settings {
public:
    Settings();
    void display(sf::RenderWindow& window);

private:
    void settingScreen();
    void handleEvents(sf::RenderWindow& window);
    void openWelcome();

    sf::Text player1NameText, player2NameText, timerText;
    sf::Font font;
    sf::RectangleShape backButton, nextButton;
    sf::Text backText, nextText;
    sf::Text player1Input, player2Input;
    std::string player1Name, player2Name;
    float timerLimit;
    bool timerSet;
    BoardTheme* selectedBoardTheme;
};

#endif // SETTINGS_HPP