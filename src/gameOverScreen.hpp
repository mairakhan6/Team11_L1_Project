#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <SFML/Graphics.hpp>

class GameOverScreen {
public:
    GameOverScreen(sf::RenderWindow& window);  // Constructor that takes a window for rendering
    void displayWinner(bool whiteWon);  // Displays the winner message
    void draw();  // Draws the screen
    bool isClosed(sf::Event& event);  // Handles events to close the screen

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text message;
};

#endif // GAMEOVERSCREEN_HPP