#include "Board.hpp"
#include <iostream>

Board::Board(const std::string& theme, const std::string& player1, const std::string& player2, int timerLimit) 
    : boardTheme(theme), timerLimit(timerLimit), lightColor(sf::Color::White), darkColor(sf::Color::Black) {

    setTheme(theme);
    loadResources();
    setPlayerInfo(player1, player2);
    setupBoardPosition();
}

Board::Board() : boardTheme("Classic"), timerLimit(60), lightColor(sf::Color::White), darkColor(sf::Color::Black) {
    loadResources();
    setupBoardPosition();
}

void Board::loadResources() {
    if (!font.loadFromFile("src/fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("src/images/bkgd.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void Board::setupBoardPosition() {
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float boardSize = 600.f;
    boardShape.setSize(sf::Vector2f(boardSize, boardSize));
    boardShape.setPosition(30.f, (textureSize.y - boardSize) / 2.f);
}

void Board::setTheme(const std::string& theme) {
    if (theme == "Classic") {
        lightColor = sf::Color::White;
        darkColor = sf::Color::Black;
    }
    else if (theme == "Pakistan") {
        lightColor = sf::Color(0, 204, 0); 
        darkColor = sf::Color(255, 255, 255); 
    }
    else if (theme == "Habib University") {
        lightColor = sf::Color(128, 0, 128); 
        darkColor = sf::Color(255, 255, 102);
    }
    else if (theme == "Ocean") {
        lightColor = sf::Color(0, 191, 255); 
        darkColor = sf::Color(0, 0, 139);
    }
    else {
        std::cerr << "Unknown theme: " << theme << std::endl;
    }
}

void Board::setPlayerInfo(const std::string& player1, const std::string& player2) {
    // Convert the timerLimit to hours, minutes, and seconds
    int hours = timerLimit / 3600;
    int minutes = (timerLimit % 3600) / 60;
    int seconds = timerLimit % 60;

    // Format the time as hh:mm:ss
    std::string formattedTime = (hours < 10 ? "0" : "") + std::to_string(hours) + ":" +
                                (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                                (seconds < 10 ? "0" : "") + std::to_string(seconds);

    // Display player 1 info
    player1Info.setFont(font);
    player1Info.setString("Player 1: " + player1 + "\nTime Limit:\n " + formattedTime);
    player1Info.setCharacterSize(20);
    player1Info.setFillColor(sf::Color(139, 69, 19));
    player1Info.setPosition(640.f, 100.f);

    // Display player 2 info
    player2Info.setFont(font);
    player2Info.setString("Player 2: " + player2 + "\nTime Limit:\n " + formattedTime);
    player2Info.setCharacterSize(20);
    player2Info.setFillColor(sf::Color(139, 69, 19));
    player2Info.setPosition(640.f, 400.f);

    // Setup Restart button
    restartButton.setFont(font);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(20);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(660.f, 250.f);

    // Setup Quit button
    quitButton.setFont(font);
    quitButton.setString("Quit");
    quitButton.setCharacterSize(20);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(660.f, 300.f);

    // Setup Restart button background
    restartButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    restartButtonBg.setFillColor(sf::Color(139, 69, 19)); // Brown color
    restartButtonBg.setPosition(645.f, 245.f); // Slightly offset from text

    // Setup Quit button background
    quitButtonBg.setSize(sf::Vector2f(120.f, 40.f)); // Width and height
    quitButtonBg.setFillColor(sf::Color(139, 69, 19)); // Brown color
    quitButtonBg.setPosition(645.f, 295.f);
}


void Board::drawGrid(sf::RenderWindow& window) {
    float squareSize = boardShape.getSize().x / 8;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(boardShape.getPosition().x + i * squareSize, boardShape.getPosition().y + j * squareSize);

            if ((i + j) % 2 == 0)
                square.setFillColor(lightColor);
            else
                square.setFillColor(darkColor);

            window.draw(square);
        }
    }
}

void Board::drawBoard(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    drawGrid(window);
    window.draw(player1Info);
    window.draw(player2Info);

    window.draw(restartButtonBg);
    window.draw(restartButton);

    // Draw Quit button with background
    window.draw(quitButtonBg);
    window.draw(quitButton);
}

sf::Texture& Board::getBackgroundTexture() {
    return backgroundTexture;
}


void Board::eventHandle(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "Mouse position: (" << mousePos.x << ", " << mousePos.y << ")\n";  // Debugging line

            if (restartButtonBg.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Restart button clicked\n";  // Debugging line
                restartGame();  // Restart the game
            }
            else if (quitButtonBg.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Quit button clicked\n";  // Debugging line
                window.close();  // Close the window
            }
        }
    }
}


void Board::restartGame() {
    // Reset game-related variables (board state, player turns)
    setPlayerInfo("Player 1", "Player 2"); // Reset player names
    
}


void Board::updateTheme(const std::string& theme) {
    setTheme(theme); // Update theme colors
}

void Board::setTimerLimit(int newTimerLimit) {
    timerLimit = newTimerLimit;
}


