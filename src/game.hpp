#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "pieces.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "gameOverScreen.hpp"

class Game : public sf::Drawable
{
public:
    Game(sf::RenderWindow& window, sf::Color c1, sf::Color c2, const std::string& player1, const std::string& player2, int timerLimit);
    void Start(sf::Color c1, sf::Color c2);
    void DrawPossibleMoves();
    bool SelectPiece(Square Cells[][8], int x, int y);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void moveSelected(Square Cells[][8], int x, int y);
    sf::Texture& getBackgroundTexture();
    bool getSelected();
    void gameOver();
    void SetRightSideofWindow();
    void handleMouseClick(sf::Vector2i mousePos);
    Square cells[8][8];
    bool isOver;
    void display(sf::RenderWindow& window);
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

    bool gameStatus, selected, whiteTurn;
    Pieces *selected_piece;
    sf::Font font;
    sf::RectangleShape infoRestart;
    sf::Text turn, situation, textRestart, chance;
    int number_of_moves;
    sf::RenderWindow& window; 
    GameOverScreen* gameOverScreen;  // Pointer to the GameOverScreen
};

#endif
