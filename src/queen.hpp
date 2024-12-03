#ifndef QUEEN_HPP
#define QUEEN_HPP
//maira
#include <vector>
#include "pieces.hpp"

using namespace std;

class Queen : public Pieces
{
public:
    Queen(int);
    vector<Square> getMoves(Square cells[][8], int x, int y);
    sf::Texture blackQueen;
    sf::Texture whiteQueen;

protected:
private:
};

#endif // QUEEN_H
