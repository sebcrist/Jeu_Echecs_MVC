#pragma once
#include "pieces.h"
class Fou : public Pieces
{
public:
	Fou(int x = 0, int y = 0, Couleur couleur = Couleur::Blanc) : Pieces(x, y, couleur, Type::Fou) {};

	bool mouvementValide(int x, int y) const override;

private:

};

