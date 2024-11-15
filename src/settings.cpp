#include "settings.hpp"
#include <iostream>

Settings::Settings() : player1Name("Player 1"), player2Name("Player 2"), timerLimit(5.0f), timerSet(false), selectedBoardTheme(nullptr) {
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // Set up the UI elements
    settingScreen();
}

void Settings::settingScreen() {
    // Back Button
    backButton.setSize(sf::Vector2f(100.f, 50.f));
    backButton.setPosition(50.f, 500.f);
    backButton.setFillColor(sf::Color::Red);
    
    // Next Button
    nextButton.setSize(sf::Vector2f(100.f, 50.f));
    nextButton.setPosition(650.f, 500.f);
    nextButton.setFillColor(sf::Color::Green);

    // Buttons Text
    backText.setFont(font);
    backText.setString("Back");
    backText.setPosition(60.f, 510.f);

    nextText.setFont(font);
    nextText.setString("Next");
    nextText.setPosition(660.f, 510.f);
}

void Settings::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Check for Back Button
                if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Going Back to Welcome Screen" << std::endl;
                    window.close(); // Close the current window
                    openWelcome();
                }

                // Check for Next Button
                if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Next button pressed. Saving player names and settings." << std::endl;
                    // Save player names and settings, and move to the game screen
                }
            }
        }
    }
}

void Settings::display(sf::RenderWindow& window) {
    window.clear();
    
    // Draw the UI elements
    window.draw(backButton);
    window.draw(nextButton);
    window.draw(backText);
    window.draw(nextText);

    handleEvents(window); // Handle events for UI
    
    window.display();
}

void Settings::openWelcome(){
    sf::RenderWindow welcomeWindow(sf::VideoMode(800, 600), "Welcome");
    Welcome welcome;
    welcome.display();
}