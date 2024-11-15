#include "welcome.hpp"
#include "settings.hpp"
#include <SFML/Graphics.hpp>

int main() {
    Welcome welcome;
    welcome.display(); // Display the welcome screen and wait for the user to close it
    return 0;
}