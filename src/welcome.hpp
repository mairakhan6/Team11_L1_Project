#ifndef WELCOME_HPP
#define WELCOME_HPP

#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "board.hpp"

class Welcome {
public:
    void display();          
    void gotoSettings();     
    void gotoBoard(Board* board); 
};

#endif
