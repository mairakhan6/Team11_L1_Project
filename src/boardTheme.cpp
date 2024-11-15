#include "boardTheme.hpp"

BoardTheme::BoardTheme(std::string name) : name(name) {}

std::string BoardTheme::getName() const {
    return name;
}