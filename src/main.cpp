#include <SFML/Graphics.hpp>
#include "welcome.hpp"
// #include "gameOverScreen.hpp"
// #include "settings.hpp"
// #include "board.hpp"
#include <iostream>

int main() {
    //Initialize Welcome screen
    Welcome welcome;
    welcome.display();  // Show Welcome screen

    // std::string name = "maira";

    // sf::RenderWindow window(sf::VideoMode(1100,800), "testerrrr");
    // GameOverScreen gameOverScreen(window, name);
    // gameOverScreen.displayWinner();


    // sf::RenderWindow window(sf::VideoMode(800, 600), "Settings");

    // // Initialize settings
    // Settings settings;
    // while (window.isOpen()) {
    //     settings.display(window);  
    // }

    
    // Board* board = settings.getBoard();  
    // if (board != nullptr) {
    //     sf::RenderWindow boardWindow(sf::VideoMode(800, 600), "Game Board");
    //     while (boardWindow.isOpen()) {
    //         sf::Event event;
    //         while (boardWindow.pollEvent(event)) {
    //             if (event.type == sf::Event::Closed) {
    //                 boardWindow.close();
    //             }

    //             // Handle button clicks
    //             board->eventHandle(boardWindow);  
    //         }

    //         boardWindow.clear();
    //         board->drawBoard(boardWindow);  // Draw the game board
    //         boardWindow.display();
    //     }
    // } else {
    //     std::cerr << "Error: Board not configured properly!" << std::endl;
    // }

    return 0;
}
