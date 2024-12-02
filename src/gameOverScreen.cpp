#include "gameOverScreen.hpp"

GameOverScreen::GameOverScreen(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("Textures/roboto.ttf")) {  // Load a font (adjust path)
        // Handle error if font is not loaded
        throw std::runtime_error("Failed to load font.");
    }

    message.setFont(font);
    message.setCharacterSize(50);
    message.setFillColor(sf::Color::White);
    message.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 50);  // Adjust position for center
}

void GameOverScreen::displayWinner(bool whiteWon) {
    if (whiteWon) {
        message.setString("CHECKMATE! \nWhite Won!!");
    } else {
        message.setString("CHECKMATE! \nBlack Won!!");
    }
}

void GameOverScreen::draw() {
    window.clear();  // Clear the window
    window.draw(message);  // Draw the winner message
    window.display();  // Display the window
}

bool GameOverScreen::isClosed(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        return true;  // Close event triggered
    }
    return false;
}