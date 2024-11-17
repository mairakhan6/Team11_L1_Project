#include "dropdown.hpp"

Dropdown::Dropdown() : expanded(false), scrollOffset(0), visibleItems(5) {
    box.setSize(sf::Vector2f(200.f, 30.f));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.f);
}

void Dropdown::setFont(const sf::Font& font) {
    this->font = font;
    selectedText.setFont(font);
    selectedText.setCharacterSize(18);
    if(selectedText.getString() =="Pakistan"){
        sf::Color customColor(80, 238, 169);
        selectedText.setFillColor(customColor);
    }
    if(selectedText.getString() =="Habib University"){
        sf::Color customColor(149, 71, 238);
        selectedText.setFillColor(customColor);
    }
    if(selectedText.getString() =="Classic"){
        sf::Color customColor(134, 75, 36);
        selectedText.setFillColor(customColor);
    }
    if(selectedText.getString() == "Ocean"){
        sf::Color customColor(51, 153, 255);
        selectedText.setFillColor(customColor);
    }
    else(selectedText.setFillColor(sf::Color::Black));
}

void Dropdown::setPosition(float x, float y) {
    box.setPosition(x, y);
    selectedText.setPosition(x + 5.f, y + 5.f);
}

void Dropdown::addItem(const std::string& item) {
    items.push_back(item);
    sf::Text itemText;
    itemText.setFont(font);
    itemText.setCharacterSize(18);
    if(item =="Pakistan"){
        sf::Color customColor(80, 238, 169);
        itemText.setFillColor(customColor);
    }
    else if(item =="Habib University"){
        sf::Color customColor(149, 71, 238);
        itemText.setFillColor(customColor);
    }
    else if(item =="Classic"){
        sf::Color customColor(134, 75, 36);
        itemText.setFillColor(customColor);
    }
    else if(item =="Ocean"){
        sf::Color customColor(51, 153, 255);
        itemText.setFillColor(customColor);
    }
    else itemText.setFillColor(sf::Color::Black);

    itemText.setString(item);
    itemText.setPosition(box.getPosition().x, box.getPosition().y + (30.f * dropdownItems.size()) + 35.f);
    dropdownItems.push_back(itemText);
}

std::string Dropdown::getSelectedItem() const {
    return selectedText.getString();
}

void Dropdown::render(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(selectedText);
    if (expanded) {
        for (size_t i = 0; i < dropdownItems.size(); ++i) {
            float yPos = box.getPosition().y + (30.f * (i - scrollOffset)) + 35.f;
            dropdownItems[i].setPosition(dropdownItems[i].getPosition().x, yPos);
            window.draw(dropdownItems[i]);
        }
    }
}

void Dropdown::handleMouse(float mouseX, float mouseY) {
    if (box.getGlobalBounds().contains(mouseX, mouseY)) {
        expanded = !expanded;
    } else if (expanded) {
        for (size_t i = 0; i < dropdownItems.size(); ++i) {
            if (dropdownItems[i].getGlobalBounds().contains(mouseX, mouseY)) {
                selectedText.setString(items[i]);

                // if (items[i] == "Pakistan") {
                //     selectedText.setFillColor(sf::Color(80, 238, 169));
                // } else if (items[i] == "Habib University") {
                //     selectedText.setFillColor(sf::Color(149, 71, 238));
                // } else if (items[i] == "Classic") {
                //     selectedText.setFillColor(sf::Color(134, 75, 36));
                // } else if (items[i] == "Ocean") {
                //     selectedText.setFillColor(sf::Color(51, 153, 255));
                // }
                // else selectedText.setFillColor(sf::Color::Black);

                selectedText.setFillColor(dropdownItems[i].getFillColor());

                expanded = false;
                break;
            }
        }
    }
}

void Dropdown::handleScroll(float delta) {
    if (expanded) {
        scrollOffset -= static_cast<int>(delta);
        scrollOffset = std::max(0, std::min(static_cast<int>(scrollOffset), static_cast<int>(items.size()) - visibleItems));
    }
}

bool Dropdown::isExpanded() const { 
    return expanded; 
}