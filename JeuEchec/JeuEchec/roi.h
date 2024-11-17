#pragma once
#include "pieces.h"
class Roi : public Pieces
{
public:	
	Roi(int x = 0, int y = 0, Couleur couleur = Couleur::Vide) : Pieces(x, y, couleur, Type::Roi) {};

	bool mouvementValide(int x, int y) const override;


private:
};

