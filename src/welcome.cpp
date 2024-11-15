#include "welcome.hpp"
#include <iostream>
using namespace std;

void Welcome::display()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "CHESS GAME");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images/welcome.jpg"))
    {
        std::cerr << "Error loading background image" << std::endl;
    }
    sf::Font font;
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    sf::Sprite background(backgroundTexture);

    sf::RectangleShape startButton(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color(92, 59, 39));
    startButton.setPosition(300.f, 300.f);
    sf::Text startButtonText("Start", font,25);
    startButtonText.setPosition(365.f, 310.f);

    //sf::Text text("شطرنج میں خوش آمدید", font);
    // sf::Text text("Welcome to the game", font);
    // text.setPosition(200,250);

    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // else if(event.type == sf::Event::KeyPressed){
            //     window.close();
            //     return; //for testing
            // }
            
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        cout <<"working"<<endl;
                        window.close();
                        gotoSettings();
                    }
                }
            }
        }
        window.clear();
        //window.draw(text);
        window.draw(background);
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();

    }
}


void Welcome::gotoSettings()
{
    sf::RenderWindow settingsWindow(sf::VideoMode(800, 600), "Settings");

    Settings settings;
    while(settingsWindow.isOpen()){
        settings.display(settingsWindow);
    }
}