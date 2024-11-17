#ifndef DROPDOWN_HPP
#define DROPDOWN_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class Dropdown
{
    private:
        
        sf::Text selectedText;
        std::vector<std::string> items;
        sf::Font font;
        bool expanded;
        std::vector<sf::Text> dropdownItems;
        int scrollOffset;
        int visibleItems;

    public:
        Dropdown();
        sf::RectangleShape box;
        void setFont(const sf::Font& font);
        void setPosition(float x, float y);
        void addItem(const std::string& item);
        string getSelectedItem() const;
        void render(sf::RenderWindow& window);
        void handleMouse(float mouseX, float mouseY);
        void handleScroll(float delta);
        bool isExpanded() const;
};

#endif
