#include "settings.hpp"
#include <iostream>
using namespace std;

Settings::Settings() :
    player1Name(""), 
    player2Name(""), 
    timerLimit(0),
    timerSet(false), 
    board(nullptr)
{
    if (!font.loadFromFile("src/fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // screen display
    settingScreen();
}

Board* Settings::getBoard() const {
    return board;
}


void Settings::settingScreen() {
    sf::Color brown(92, 59, 39);

    // Back Button
    backButton.setSize(sf::Vector2f(100.f, 50.f));
    backButton.setPosition(50.f, 500.f);
    backButton.setFillColor(brown);
    backText.setFont(font);
    backText.setString("Back");
    backText.setPosition(60.f, 510.f);
    
    // Next Button
    nextButton.setSize(sf::Vector2f(100.f, 50.f));
    nextButton.setPosition(650.f, 500.f);
    nextButton.setFillColor(brown);
    nextText.setFont(font);
    nextText.setString("Next");
    nextText.setPosition(660.f, 510.f);

    // Labels and Inputs
    player1Label.setFont(font);
    player1Label.setString("Player 1 Name:");
    player1Label.setFillColor(brown);
    player1Label.setPosition(50.f, 50.f);

    player2Label.setFont(font);
    player2Label.setString("Player 2 Name:");
    player2Label.setFillColor(brown);
    player2Label.setPosition(50.f, 150.f);

    themeLabel.setFont(font);
    themeLabel.setString("Board Theme:");
    themeLabel.setFillColor(brown);
    themeLabel.setPosition(50.f, 250.f);

    timerLabel.setFont(font);
    timerLabel.setString("Timer:");
    timerLabel.setFillColor(brown);
    timerLabel.setPosition(50.f, 350.f);

    // Player 1 Input
    player1Input.setFont(font);
    player1Input.setPosition(300.f, 52.f);
    player1Input.setString(player1Name);

    // Player 2 Input
    player2Input.setFont(font);
    player2Input.setPosition(300.f, 152.f);
    player2Input.setString(player2Name);

    // Theme Dropdown
    themeDropdown.setFont(font);
    themeDropdown.setPosition(300.f, 252.f);
    themeDropdown.addItem("Classic");
    themeDropdown.addItem("Pakistan");
    themeDropdown.addItem("Habib University");
    themeDropdown.addItem("Ocean");

    // Timer Inputs
    timerMins.setFont(font);
    timerMins.box.setSize(sf::Vector2f(80.f, 30.f));
    timerMins.setPosition(300.f, 352.f);
    for (int i = 5; i < 60; i+=5) {
        timerMins.addItem(to_string(i));
    }

    timerSecs.setFont(font);
    timerSecs.box.setSize(sf::Vector2f(80.f, 30.f));
    timerSecs.setPosition(500.f, 352.f);
    for (int i = 0; i < 60; i+=5) {
        timerSecs.addItem(to_string(i));
    }

    minsLabel.setFont(font);
    secsLabel.setFont(font);
    minsLabel.setCharacterSize(20);
    secsLabel.setCharacterSize(20);
    minsLabel.setString(" minutes");
    secsLabel.setString(" seconds");
    minsLabel.setPosition(400.f, 352.f);
    secsLabel.setPosition(600.f, 352.f);
}

void Settings::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Going Back to Welcome Screen" << std::endl;
                    window.close();  // close current window
                    openWelcome();
                }

                if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Next button pressed. Saving player names and settings." << std::endl;
                    saveSettings();
                    window.close();
                }
            }
        }

        // Inputs
        if (event.type == sf::Event::TextEntered) {
            if (player1Input.isFocus()) {
                player1Input.handleInput(event.text.unicode);
            }
            if (player2Input.isFocus()) {
                player2Input.handleInput(event.text.unicode);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            player1Input.checkFocus(event.mouseButton.x, event.mouseButton.y);
            player2Input.checkFocus(event.mouseButton.x, event.mouseButton.y);
            timerMins.handleMouse(event.mouseButton.x, event.mouseButton.y);
            timerSecs.handleMouse(event.mouseButton.x, event.mouseButton.y);
            themeDropdown.handleMouse(event.mouseButton.x, event.mouseButton.y);
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (timerMins.isExpanded()) {
                timerMins.handleScroll(event.mouseWheelScroll.delta);
            }
            else if (timerSecs.isExpanded()) {
                timerSecs.handleScroll(event.mouseWheelScroll.delta);
            }
            else if (themeDropdown.isExpanded()) {
                themeDropdown.handleScroll(event.mouseWheelScroll.delta);
            }
        }
    }
}

void Settings::display(sf::RenderWindow& window) {
    window.clear();
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/images/bkgd.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    window.draw(background);

    //player 1 
    window.draw(player1Label);
    player1Input.render(window);


    //player 2
    window.draw(player2Label);
    player2Input.render(window);

    //theme
    window.draw(themeLabel);
    themeDropdown.render(window);
    //timer
    window.draw(timerLabel);
    window.draw(minsLabel);
    window.draw(secsLabel);
    timerMins.render(window);
    timerSecs.render(window);
    //buttons 
    window.draw(backButton);
    window.draw(nextButton);
    window.draw(backText);
    window.draw(nextText);

    handleEvents(window);  // Handle events for UI

    window.display();
}

void Settings::openWelcome() {
    sf::RenderWindow welcomeWindow(sf::VideoMode(800, 600), "Welcome");
    Welcome welcome;
    welcome.display();  // Go back to Welcome screen
}

void Settings::saveSettings() {
    player1Name = player1Input.getString();
    player2Name = player2Input.getString();

    string minsStr = timerMins.getSelectedItem();
    string secsStr = timerSecs.getSelectedItem();
    timerLimit = (stoi(minsStr) * 60) + stoi(secsStr);

    // Create a new Board with the selected theme and other settings
    board = new Board(themeDropdown.getSelectedItem(), player1Name, player2Name, timerLimit);
}
