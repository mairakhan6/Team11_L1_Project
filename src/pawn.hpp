#ifndef PAWN_HPP
#define PAWN_HPP

#include <iostream>
#include <vector>
#include "square.hpp"
#include "pieces.hpp"

class Pawn : public Pieces
{
public:
    Pawn(int);
    std::vector<Square> getMoves(Square cells[][8], int x, int y);
    sf::Texture blackPawn;
    sf::Texture whitePawn;

protected:
};

#endif // PAWN_H
