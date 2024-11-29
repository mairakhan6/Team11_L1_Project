#include "timer.hpp"
#include <iostream>

Timer::Timer(){
    if (!font.loadFromFile("src/fonts/english.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
}

Timer::Timer(float timeLimit) : timeLimit(timeLimit), timeRemaining(timeLimit), running(false) {
    if (!font.loadFromFile("src/fonts/english.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
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

void Timer::update(float deltaTime) {
    if (running) {
        timeRemaining -= deltaTime;
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

float Timer::getTimeLeft() const {
    return timeRemaining;
}

void Timer::draw(sf::RenderWindow& window) {
    int minutes = static_cast<int>(timeRemaining) / 60;
    int seconds = static_cast<int>(timeRemaining) % 60;
    std::string timeStr = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    timeText.setString(timeStr);
    timeText.setPosition(350.f, 20.f);
    window.draw(timeText);
}