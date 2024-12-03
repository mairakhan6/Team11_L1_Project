#include "welcome.hpp"
#include <iostream>
using namespace std;

void Welcome::display() {
    sf::RenderWindow window(sf::VideoMode(1100, 800), "CHESS GAME");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/welcome.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    }
    sf::Font font;
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    sf::Sprite background(backgroundTexture);

    sf::RectangleShape startButton(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color(92, 59, 39));
    startButton.setPosition(450.f, 450.f);
    sf::Text startButtonText("Start", font, 25);
    startButtonText.setPosition(515.f, 460.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        cout << "working" << endl;
                        window.close();
                        gotoSettings();  
                    }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();
    }
}

void Welcome::gotoSettings() {
    sf::RenderWindow settingsWindow(sf::VideoMode(1100, 800), "Settings");

    Settings settings;
    while (settingsWindow.isOpen()) {
        settings.display(settingsWindow);  
    }

    
    // Board* configuredBoard = settings.getBoard();
    // if (configuredBoard) {
    //     gotoBoard(configuredBoard);  
    // } else {
    //     std::cerr << "Error: No board configured!" << std::endl;
    // }
}

void Welcome::gotoBoard(Board* board) {

    //laiba-
    sf::RenderWindow boardWindow(sf::VideoMode(800, 600), "Game Board");

    while (boardWindow.isOpen()) {
        sf::Event event;
        while (boardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                boardWindow.close();
            }
            
        }

        boardWindow.clear();  // Clear the screen

        // Draw the board
        if (board) {
            board->drawBoard(boardWindow);  
        }

        boardWindow.display();  
    }

    delete board;  
}
