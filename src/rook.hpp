#ifndef ROOK_HPP
#define ROOK_HPP
#include "pieces.hpp"
#include <vector>
using namespace std;
//maira
class Rook : public Pieces
{
public:
  Rook(int);
  vector<Square> getMoves(Square cells[][8], int x, int y);
  sf::Texture blackRook;
  sf::Texture whiteRook;

protected:
private:
};

#endif // ROOK_H
