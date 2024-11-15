#ifndef BOARD_THEME_HPP
#define BOARD_THEME_HPP

#include <string>
using namespace std;

class BoardTheme 
{
    private:
        std::string name;
    public:
        BoardTheme(std::string name);
        string getName() const;

};

#endif