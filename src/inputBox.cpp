#include "inputBox.hpp"

InputBox::InputBox() : focused(false) {
    box.setSize(sf::Vector2f(200.f, 30.f));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);
}

void InputBox::setFont(const sf::Font& font) {
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
}

void InputBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 5.f, y + 5.f);
}

void InputBox::setString(const std::string& textStr) {
    text.setString(textStr);
}

std::string InputBox::getString() const {
    return text.getString();
}

void InputBox::render(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}

void InputBox::handleInput(sf::Uint32 unicode) {
    if (focused) {
        if (unicode == 8) { // Backspace
            std::string currentText = text.getString();
            if (!currentText.empty()) {
                currentText.pop_back();
                text.setString(currentText);
            }
        } else if (unicode >= 32 && unicode <= 126) { // Printable characters
            text.setString(text.getString() + static_cast<char>(unicode));
        }
    }
}

void InputBox::checkFocus(float mouseX, float mouseY) {
    focused = box.getGlobalBounds().contains(mouseX, mouseY);
    box.setOutlineColor(focused ? sf::Color::Blue : sf::Color::Black);
}

bool InputBox::isFocus() const {
    return focused;
}