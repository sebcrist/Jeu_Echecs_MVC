#pragma once
#include "pieces.h"
class Cavalier : public Pieces
{
public:
	Cavalier(int x = 0, int y = 0, Couleur couleur = Couleur::Vide) : Pieces(x, y, couleur, Type::Cavalier) {};

	bool mouvementValide(int x, int y) const override;


private:


};

