#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Piece {
private:
    sf::Sprite sprite;
    sf::Vector2i position; // board position (0-7, 0-7)
    bool isWhite;
    std::string type; // "pawn", "rook", "knight", "bishop", "queen", "king"
    static sf::Vector2f boardPosition;
    static float squareSize;

public:
    Piece(const std::string& type, bool isWhite, int x, int y);
    void setTexture(const sf::Texture& texture);
    void setPosition(int x, int y);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getPosition() const;
    bool getIsWhite() const;
    std::string getType() const;
    
    static void setBoardProperties(const sf::Vector2f& pos, float size) {
        boardPosition = pos;
        squareSize = size;
    }
};

#endif // PIECE_HPP