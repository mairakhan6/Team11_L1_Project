#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "square.hpp"
using namespace std;

class Pieces
{
public:
    vector<Square> possibleMoves;
    virtual vector<Square> getMoves(Square Cells[][8], int x, int y) = 0;
    int x, y;
    bool isAlive;
    bool isWhite;
    bool occupied_color;
    int occupied_value;
    sf::Sprite piece;
};

#endif // PIECES_H
