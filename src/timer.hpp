#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Timer 
{
    private:
        float timeLimit;
        float timeRemaining;
        bool running;
        sf::Clock clock;
        sf::Text timeText;
        sf::Font font;

    public:
        Timer();
        Timer(float timeLimit); 
        void start();
        void stop();
        void reset();
        void update(float deltaTime);
        void setTimeLimit(float timeLimit);
        float getTimeLeft() const;
        void draw(sf::RenderWindow& window) ;

};

#endif 