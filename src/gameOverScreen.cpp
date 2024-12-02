#include "gameOverScreen.hpp"
#include <iostream>

GameOverScreen::GameOverScreen(sf::RenderWindow& window, std::string& winner) : window(window), winner(winner) {
    if (!font.loadFromFile("fonts/english.ttf")) {  // Load a font (adjust path)
        // Handle error if font is not loaded
        throw std::runtime_error("Failed to load font.");
    }

    message.setFont(font);
    message.setCharacterSize(50);
    message.setFillColor(sf::Color(92, 59, 39));
    message.setPosition(window.getSize().x / 2 - 150, 350);  // Adjust position for center
}

void GameOverScreen::displayWinner() {
    // if (whiteWon) {
    //     message.setString("CHECKMATE! \nWhite Won!!");
    // } else {
    //     message.setString("CHECKMATE! \nBlack Won!!");
    // }

    message.setString(winner + " Won!!");
}

void GameOverScreen::draw() {
    window.clear();  // Clear the window
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/end.png")) {
        std::cerr << "Error loading background image" << std::endl;
    }
    sf::Sprite background(backgroundTexture);

    playAgainBg.setSize(sf::Vector2f(200.f, 50.f));
    playAgainBg.setFillColor(sf::Color(92, 59, 39));
    playAgainBg.setPosition(20.f, 730.f);

    // sf::Text playAgainText("Play Again", font, 25);
    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setCharacterSize(25);
    playAgainText.setPosition(50.f, 740.f);

    quitBg.setSize(sf::Vector2f(200.f, 50.f));
    quitBg.setFillColor(sf::Color(92, 59, 39));
    quitBg.setPosition(880.f, 730.f);

    // sf::Text playAgainText("Play Again", font, 25);
    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setFillColor(sf::Color::White);
    quitText.setCharacterSize(25);
    quitText.setPosition(950.f, 740.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                    if (playAgainBg.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // cout << "working" << endl;
                        window.close();
                        gotoSettings();  
                    }

                    else if(quitBg.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close();
                    }
            }


    window.draw(background);
    window.draw(message);  // Draw the winner message
    window.draw(playAgainBg);
    window.draw(playAgainText);
    window.draw(quitBg);
    window.draw(quitText);
    window.display();  // Display the window
        }
    }
}

bool GameOverScreen::isClosed(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        return true;  // Close event triggered
    }
    return false;
}

void GameOverScreen::gotoSettings() {
    sf::RenderWindow settingsWindow(sf::VideoMode(1100, 800), "Settings");
    Settings settings;
    while (settingsWindow.isOpen()) {
        settings.display(settingsWindow);  
    }
}