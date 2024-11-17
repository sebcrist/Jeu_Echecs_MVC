#pragma once
#include "pieces.h"

class Tour : public Pieces
{
public:
	Tour(int x = 0, int y = 0, Couleur couleur = Couleur::Vide) : Pieces(x, y, couleur, Type::Tour) {};
	bool mouvementValide(int x, int y) const override;

	//static std::vector<std::pair<int, int>> generateMoves(JeuEchecControlleur* jeuEchec, int x, int y);


private:
};

