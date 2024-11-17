#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP  

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class InputBox
{
    private:
        sf::RectangleShape box;
        sf::Text text;
        bool focused;

    public:
        InputBox();
        void setFont(const sf::Font &font);
        void setPosition(float x, float y);
        void setString(const string &str);
        string getString() const;
        void render(sf::RenderWindow &window);
        void handleInput(sf::Uint32 unicode);
        void checkFocus(float mouseX, float mouseY);
        bool isFocus() const;
        
};


#endif