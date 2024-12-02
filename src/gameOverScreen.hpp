#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "settings.hpp"

class GameOverScreen {
public:
    GameOverScreen(sf::RenderWindow& window, std::string& winner);  // Constructor that takes a window for rendering
    void displayWinner();  // Displays the winner message
    void draw();  // Draws the screen
    std::string& winner;  // Reference to the winner string
    bool isClosed(sf::Event& event);  // Handles events to close the screen

    void gotoSettings();     

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text message;

    mutable sf::Text playAgainText;
    mutable sf::Text quitText;

    mutable sf::RectangleShape playAgainBg;
    mutable sf::RectangleShape quitBg;
    
};

#endif // GAMEOVERSCREEN_HPP