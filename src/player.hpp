#ifndef PLAYER_HPP  
#define PLAYER_HPP
#include <string>
#include <SFML/Graphics.hpp>
#include "timer.hpp"
using namespace std;

class Player
{
    private:
        string name;
        bool isWhite;
        Timer timer;
    public:
        Player();
        Player(string name, bool isWhite, float timeLimit);
        // in settings, when u enter name 
        string getName() const;
        void setName(const string& name);
        //assign a position to the player
        bool getIsWhite() const;
        void setIsWhite(bool isWhite);
        //timer for when its their turn
        void updateTimer(float deltaTime);
        void drawTimer(sf::RenderWindow& window);
};

#endif 