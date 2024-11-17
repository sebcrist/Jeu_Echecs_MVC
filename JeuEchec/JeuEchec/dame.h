#pragma once
#include "pieces.h"
class Dame : public Pieces
{
public:
	Dame(int x = 0, int y = 0, Couleur couleur = Couleur::Vide) : Pieces(x, y, couleur, Type::Dame) {};

	bool mouvementValide(int x, int y) const override;

private:
};

