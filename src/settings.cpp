#include "settings.hpp"
#include "game.hpp"
#include <iostream>
using namespace std;
//maira
Settings::Settings() :
    player1Name(""), 
    player2Name(""), 
    timerLimit(0),
    timerSet(false), 
    board(nullptr)
{
    if (!font.loadFromFile("fonts/english.ttf")) {
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
    backButton.setSize(sf::Vector2f(200.f, 50.f));
    backButton.setPosition(50.f, 730.f);
    backButton.setFillColor(brown);
    backText.setFont(font);
    backText.setString("Back");
    backText.setPosition(100.f, 740.f);
    
    // Next Button
    nextButton.setSize(sf::Vector2f(200.f, 50.f));
    nextButton.setPosition(860.f, 730.f);
    nextButton.setFillColor(brown);
    nextText.setFont(font);
    nextText.setString("Next");
    nextText.setPosition(930.f, 740.f);

    // Labels and Inputs
    player1Label.setFont(font);
    player1Label.setString("Player 1 Name:");
    player1Label.setFillColor(brown);
    player1Label.setPosition(50.f, 50.f);

    player2Label.setFont(font);
    player2Label.setString("Player 2 Name:");
    player2Label.setFillColor(brown);
    player2Label.setPosition(50.f, 200.f);

    themeLabel.setFont(font);
    themeLabel.setString("Board Theme:");
    themeLabel.setFillColor(brown);
    themeLabel.setPosition(50.f, 350.f);

    timerLabel.setFont(font);
    timerLabel.setString("Timer:");
    timerLabel.setFillColor(brown);
    timerLabel.setPosition(50.f, 550.f);

    // Player 1 Input
    player1Input.setFont(font);
    player1Input.setPosition(300.f, 52.f);
    player1Input.setString(player1Name);

    // Player 2 Input
    player2Input.setFont(font);
    player2Input.setPosition(300.f, 202.f);
    player2Input.setString(player2Name);

    // Theme Dropdown
    themeDropdown.setFont(font);
    themeDropdown.setPosition(300.f, 352.f);
    themeDropdown.addItem("Classic");
    themeDropdown.addItem("Pakistan");
    themeDropdown.addItem("Habib University");
    themeDropdown.addItem("Ocean");

    // Timer Inputs
    timerMins.setFont(font);
    timerMins.box.setSize(sf::Vector2f(80.f, 30.f));
    timerMins.setPosition(300.f, 552.f);
    for (int i = 5; i < 60; i+=5) {
        timerMins.addItem(to_string(i));
    }

    timerSecs.setFont(font);
    timerSecs.box.setSize(sf::Vector2f(80.f, 30.f));
    timerSecs.setPosition(500.f, 552.f);
    for (int i = 0; i < 60; i+=5) {
        timerSecs.addItem(to_string(i));
    }

    minsLabel.setFont(font);
    secsLabel.setFont(font);
    minsLabel.setFillColor(brown);
    secsLabel.setFillColor(brown);
    minsLabel.setCharacterSize(20);
    secsLabel.setCharacterSize(20);
    minsLabel.setString(" minutes");
    secsLabel.setString(" seconds");
    minsLabel.setPosition(400.f, 552.f);
    secsLabel.setPosition(600.f, 552.f);
}

void Settings::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
                if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Going Back to Welcome Screen" << std::endl;
                    window.close();  // close current window
                    openWelcome();
                }

                if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Next button pressed. Saving player names and settings." << std::endl;
                    window.close();
                    saveSettings();
                    
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
    if (!backgroundTexture.loadFromFile("images/bkgd.jpg")) {
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
    // sf::RenderWindow welcomeWindow(sf::VideoMode(1100, 800), "Welcome");
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

    //laiba-
    board = new Board(themeDropdown.getSelectedItem(), player1Name, player2Name, timerLimit);

    string theme = themeDropdown.getSelectedItem();
    sf::RenderWindow gameWindow(sf::VideoMode(1100, 800), "Game");
    if (theme == "Classic"){
        Game chess(gameWindow, sf::Color(119,67,22), sf::Color(198,141,92), player1Name, player2Name, timerLimit,theme);
        chess.display(gameWindow);
    }
    else if(theme == "Pakistan"){
        Game chess(gameWindow, sf::Color(11, 175, 11), sf::Color(255, 255, 255), player1Name, player2Name, timerLimit, theme);
        chess.display(gameWindow);
    }
    else if(theme == "Habib University"){
        Game chess(gameWindow, sf::Color(98, 0, 128), sf::Color(252, 252, 152), player1Name, player2Name, timerLimit,theme);
        chess.display(gameWindow);
    }
    else if(theme == "Ocean"){
        Game chess(gameWindow, sf::Color(11, 136, 182), sf::Color(0, 0, 139), player1Name, player2Name, timerLimit, theme);
        chess.display(gameWindow);
    }
    
}
