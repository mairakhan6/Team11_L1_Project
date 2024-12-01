#include "piece.hpp"

// Initialize static members
sf::Vector2f Piece::boardPosition;
float Piece::squareSize = 0;

Piece::Piece(const std::string& type, bool isWhite, int x, int y)
    : type(type), isWhite(isWhite), position(x, y) {}

void Piece::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
    // Calculate scale based on square size and texture size
    float scale = (squareSize * 0.7f) / std::max(texture.getSize().x, texture.getSize().y); // 70% of square size
    sprite.setScale(scale, scale);
}

void Piece::setPosition(int x, int y) {
    position = sf::Vector2i(x, y);
    // Convert board position to screen coordinates
    float screenX = boardPosition.x + (x * squareSize);
    float screenY = boardPosition.y + (y * squareSize);
    
    // Center the piece in the square
    float pieceWidth = sprite.getGlobalBounds().width;
    float pieceHeight = sprite.getGlobalBounds().height;
    float offsetX = (squareSize - pieceWidth) / 2;
    float offsetY = (squareSize - pieceHeight) / 2;
    
    sprite.setPosition(screenX + offsetX, screenY + offsetY);
}

void Piece::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2i Piece::getPosition() const {
    return position;
}

bool Piece::getIsWhite() const {
    return isWhite;
}

std::string Piece::getType() const {
    return type;
}