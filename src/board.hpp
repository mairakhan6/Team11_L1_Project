#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Board {
public:
    // Constructors
    Board(const std::string& theme, const std::string& player1, const std::string& player2, int timerLimit);
    Board();

    // Public methods
    void drawGrid(sf::RenderWindow& window);
    void drawBoard(sf::RenderWindow& window);
    sf::Texture& getBackgroundTexture();
    void eventHandle(sf::RenderWindow& window);

private:
    // Private methods
    void loadResources();        // Load font and background image
    void setupBoardPosition();   // Set up the board position and size
    void setTheme(const std::string& theme); // Set the theme for the board
    void setPlayerInfo(const std::string& player1, const std::string& player2); // Set player info (names)
    void updateTheme(const std::string& theme);
    void setTimerLimit(int newTimerLimit); 
    void restartGame();

    // Member variables
    sf::RectangleShape boardShape;        // Shape of the board
    sf::Font font;                       // Font for text
    sf::Text player1Info;                // Text for player 1 info
    sf::Text player2Info;                // Text for player 2 info
    sf::Text restartButton;
    sf::Text quitButton;

    sf::RectangleShape restartButtonBg;
    sf::RectangleShape quitButtonBg;


    sf::Sprite backgroundSprite;         // Background sprite
    sf::Texture backgroundTexture;       
    sf::Color lightColor;                // Color for light squares
    sf::Color darkColor;                 // Color for dark squares
    std::string player1Name;             // Player 1's name
    std::string player2Name;             // Player 2's name
    std::string boardTheme;              // Board theme
    int timerLimit;                      // Timer limit
};

#endif // BOARD_HPP
