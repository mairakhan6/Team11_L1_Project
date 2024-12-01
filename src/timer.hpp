#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Timer {
private:
    float timeLimit;
    float timeRemaining;
    bool running;
    sf::Clock clock;
    sf::Text timeText;
    sf::Font font;
    sf::Vector2f position;  // Add position for flexible placement

public:
    Timer();
    Timer(float timeLimit, const sf::Vector2f& pos = sf::Vector2f(350.f, 20.f));
    void start();
    void stop();
    void reset();
    void update();  // Remove deltaTime parameter, use clock instead
    void setTimeLimit(float timeLimit);
    void setPosition(const sf::Vector2f& pos);
    float getTimeLeft() const;
    bool isTimeUp() const;  // Add method to check if time is up
    void draw(sf::RenderWindow& window);
};

#endif