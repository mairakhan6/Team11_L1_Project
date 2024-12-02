#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <vector>
#include "square.hpp"
#include "pieces.hpp"
using namespace std;

class Knight : public Pieces
{
public:
    Knight(int);
    vector<Square> getMoves(Square cells[][8], int x, int y);
    sf::Texture whiteKnight;
    sf::Texture blackKnight;

protected:
private:
};

#endif 
