#include "settings.hpp"
#include <iostream>
using namespace std;


Settings::Settings() : 
    player1Name(""), 
    player2Name(""), 
    timerLimit(), 
    timerSet(false), 
    boardTheme(nullptr) 
    {
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    // screen display
    settingScreen();
}

void Settings::settingScreen() 
{
    sf::Color brown(92, 59, 39);
    // back button
    backButton.setSize(sf::Vector2f(100.f, 50.f));
    backButton.setPosition(50.f, 500.f);
    backButton.setFillColor(brown);
    backText.setFont(font);
    backText.setString("Back");
    backText.setPosition(60.f, 510.f);
    
    // next button
    nextButton.setSize(sf::Vector2f(100.f, 50.f));
    nextButton.setPosition(650.f, 500.f);
    nextButton.setFillColor(brown);
    nextText.setFont(font);
    nextText.setString("Next");
    nextText.setPosition(660.f, 510.f);

    // ALL LABELS :

    // player 1 name 
    player1Label.setFont(font);
    player1Label.setString("Player 1 Name:");
    player1Label.setFillColor(brown);
    player1Label.setPosition(50.f, 50.f);

    //player 2 name 
    player2Label.setFont(font);
    player2Label.setString("Player 2 Name:");
    player2Label.setFillColor(brown);
    player2Label.setPosition(50.f, 150.f);

    // theme label
    themeLabel.setFont(font);
    themeLabel.setString("Board Theme:");
    themeLabel.setFillColor(brown);
    themeLabel.setPosition(50.f, 250.f);

    // timer label
    timerLabel.setFont(font);
    timerLabel.setString("Timer:");
    timerLabel.setFillColor(brown);
    timerLabel.setPosition(50.f, 350.f);

    // ALL INPUTS:

    // player 1 input
    player1Input.setFont(font);
    player1Input.setPosition(300.f, 52.f);
    player1Input.setString(player1Name);

    // player 2 input
    player2Input.setFont(font);
    player2Input.setPosition(300.f, 152.f);
    player2Input.setString(player2Name);

    // theme dropdown
    themeDropdown.setFont(font);
    themeDropdown.setPosition(300.f, 252.f);
    themeDropdown.addItem("Classic");
    themeDropdown.addItem("Pakistan");
    themeDropdown.addItem("Habib University");
    themeDropdown.addItem("Ocean");

    // timer input
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
    // timerInput.setFont(font);
    // timerInput.setPosition(250.f, 260.f);
    // timerInput.setString(to_string(timerLimit));

    minsLabel.setFont(font);
    secsLabel.setFont(font);
    minsLabel.setCharacterSize(20);
    secsLabel.setCharacterSize(20);
    minsLabel.setString(" minutes");
    secsLabel.setString(" seconds");
    minsLabel.setPosition(400.f, 352.f);
    secsLabel.setPosition(600.f, 352.f);

}

void Settings::handleEvents(sf::RenderWindow& window) 
{
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
                    window.close(); // close current window
                    openWelcome();
                }

                // Check for Next Button
                if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Next button pressed. Saving player names and settings." << std::endl;
                    saveSettings();
                    window.close();
                    // move to game !!
                }
            }
        }

        //inputs
        if(event.type == sf::Event::TextEntered){
            if(player1Input.isFocus()){
                player1Input.handleInput(event.text.unicode);
            }
            if(player2Input.isFocus()){
                player2Input.handleInput(event.text.unicode);
            }
        }

        if(event.type == sf::Event::MouseButtonPressed){
            player1Input.checkFocus(event.mouseButton.x, event.mouseButton.y);
            player2Input.checkFocus(event.mouseButton.x, event.mouseButton.y);
            timerMins.handleMouse(event.mouseButton.x, event.mouseButton.y);
            timerSecs.handleMouse(event.mouseButton.x, event.mouseButton.y);
            themeDropdown.handleMouse(event.mouseButton.x, event.mouseButton.y);
        }

        if(event.type == sf::Event::MouseWheelScrolled){
            if(timerMins.isExpanded()){
                timerMins.handleScroll(event.mouseWheelScroll.delta);
            }
            else if(timerSecs.isExpanded()){
                timerSecs.handleScroll(event.mouseWheelScroll.delta);
            }
            else if(themeDropdown.isExpanded()){
                themeDropdown.handleScroll(event.mouseWheelScroll.delta);
            }
        }
    }
}

void Settings::display(sf::RenderWindow& window) 
{
    window.clear();
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/bkgd.jpg"))
    {
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
    // timerInput.render(window);
    timerMins.render(window);
    timerSecs.render(window);
    //buttons
    window.draw(backButton);
    window.draw(nextButton);
    window.draw(backText);
    window.draw(nextText);

    handleEvents(window); // Handle events for UI
    
    window.display();
}

void Settings::openWelcome()
{
    sf::RenderWindow welcomeWindow(sf::VideoMode(800, 600), "Welcome");
    Welcome welcome;
    welcome.display();
}

void Settings::saveSettings()
{
    player1Name = player1Input.getString();
    player2Name = player2Input.getString();

    string minsStr = timerMins.getSelectedItem();
    string secsStr = timerSecs.getSelectedItem();
    int minutes = std::stoi(minsStr);
    int seconds = std::stoi(secsStr);

    timer.setTimeLimit(static_cast<float>(minutes * 60 + seconds));

    boardTheme = new BoardTheme(themeDropdown.getSelectedItem());
}