#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <iostream>
#include <vector>
#include "pieces.hpp"
using namespace std;

class Bishop : public Pieces
{
public:
    Bishop(int color);

    vector<Square> getMoves(Square cells[][8], int x, int y);
    sf::Texture blackBishop;
    sf::Texture whiteBishop;

};

#endif 
