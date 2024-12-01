#include "timer.hpp"
#include <iostream>

Timer::Timer() {
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    position = sf::Vector2f(350.f, 20.f);
    timeText.setPosition(position);
}

Timer::Timer(float timeLimit, const sf::Vector2f& pos) 
    : timeLimit(timeLimit), timeRemaining(timeLimit), running(false), position(pos) {
    if (!font.loadFromFile("fonts/english.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(position);
}

void Timer::start() {
    if (!running) {
        clock.restart();
        running = true;
    }
}

void Timer::stop() {
    if (running) {
        running = false;
    }
}

void Timer::reset() {
    timeRemaining = timeLimit;
    if (running) {
        clock.restart();
    }
}

void Timer::update() {
    if (running) {
        float elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timeRemaining -= elapsed;
        if (timeRemaining <= 0) {
            timeRemaining = 0;
            stop();
        }
    }
}

void Timer::setTimeLimit(float timeLimit) {
    this->timeLimit = timeLimit;
    this->timeRemaining = timeLimit;
}

void Timer::setPosition(const sf::Vector2f& pos) {
    position = pos;
    timeText.setPosition(position);
}

float Timer::getTimeLeft() const {
    return timeRemaining;
}

bool Timer::isTimeUp() const {
    return timeRemaining <= 0;
}

void Timer::draw(sf::RenderWindow& window) {
    int minutes = static_cast<int>(timeRemaining) / 60;
    int seconds = static_cast<int>(timeRemaining) % 60;
    std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    timeText.setString(timeStr);
    window.draw(timeText);
}
