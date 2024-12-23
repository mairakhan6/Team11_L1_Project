#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "gameOverScreen.hpp"
#include "pieces.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "timer.hpp"

class Game : public sf::Drawable
{
public:
    Game(sf::RenderWindow& window, sf::Color c1, sf::Color c2, const std::string& player1, const std::string& player2, int timerLimit, const std::string& theme);
    void Start(sf::Color c1, sf::Color c2);
    void DrawPossibleMoves();
    bool SelectPiece(Square Cells[][8], int x, int y);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void moveSelected(Square Cells[][8], int x, int y);
    sf::Texture& getBackgroundTexture();
    bool getSelected();
    void gameOver();
    void SetRightSideofWindow();
    void handleEvents(sf::RenderWindow& window);
    void setPlayerInfo(const std::string& player1, const std::string& player2);
    Square cells[8][8];
    bool isOver;
    void display(sf::RenderWindow& window);

    void startGame();

private:
    vector<Square> moves;
    vector<sf::RectangleShape> newmoves;
    vector<Pieces *> whitePieces;
    vector<Pieces *> blackPieces;
    // white pieces
    King *w_king;
    Queen *w_queen;
    Bishop *w_bishop[2];
    Rook *w_rook[2];
    Knight *w_knight[2];
    Pawn *w_pawn[8];
    // black pieces
    King *b_king;
    Queen *b_queen;
    Bishop *b_bishop[2];
    Rook *b_rook[2];
    Knight *b_knight[2];
    Pawn *b_pawn[8];

    mutable bool gameStatus;
    bool selected, whiteTurn;
    Pieces *selected_piece;
    sf::Font font;
    //sf::RectangleShape infoRestart;
    sf::Text turn, situation, textRestart, chance;
    int number_of_moves;
    sf::RenderWindow& window; 
    GameOverScreen* gameOverScreen;  // Pointer to the GameOverScreen

    sf::Sprite backgroundSprite;         // Background sprite
    sf::Texture backgroundTexture; 
    std::string player1Name;             // Player 1's name
    std::string player2Name;   
    const std::string& theme;          // Player 2's name
    int timerLimit;                      // Timer limit
    mutable Timer player1Timer;          //Player 1's Timer
    mutable Timer player2Timer;          //Player 2's Timer

    mutable sf::Text player1Info;                // Text for player 1 info
    mutable sf::Text player2Info;                // Text for player 2 info
    mutable sf::Text startButton;
    mutable sf::Text restartButton;
    mutable sf::ConvexShape arrow;
    mutable sf::CircleShape circle;
    mutable sf::Text quitButton;

    mutable sf::RectangleShape startButtonBg;
    mutable sf::RectangleShape restartButtonBg;
    mutable sf::RectangleShape quitButtonBg;

    mutable std::string formatTime(float seconds) const;
    void restartGame();
};

#endif
