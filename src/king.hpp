#ifndef KING_HPP
#define KING_HPP

#include <vector>
#include "square.hpp"
#include "pieces.hpp"

class King : public Pieces
{
public:
    King(int);
    bool isStaleMate(Square Cells[][8], int x, int y);
    bool isCheck(Square Cells[][8], int x, int y);
    bool isCheckmate(Square Cells[][8], int x, int y);
    vector<Square> getMoves(Square cells[][8], int x, int y);
    sf::Texture blackKing;
    sf::Texture whiteKing;

protected:
private:
};

#endif // KING_HPP
