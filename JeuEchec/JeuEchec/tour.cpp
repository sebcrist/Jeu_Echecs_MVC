#pragma once
#include "tour.h"


bool Tour::mouvementValide(int x, int y) const
{
	if (x == this->getX() || y == this->getY())
	{
		return true;
	}
	else
		return false;
}

//std::vector<std::pair<int, int>> Tour::generateMoves(JeuEchecControlleur* jeuEchec, int x, int y)
//{
//	std::vector<std::pair<int, int>> positions;
//    CaseControlleur* caseJeu = jeuEchec->getCase(x, y);
//
//    for (int i = x - 1; i >= 0; --i) {
//        if (jeuEchec->getCase(i, y)->getPiece() == nullptr)
//        {
//            if (jeuEchec->getCase(i, y)->getPiece()->getCouleur() == caseJeu->getCouleur())
//                break;
//            else
//            {
//                positions.push_back(std::make_pair(i, y));
//            }
//        }
//        else
//            positions.push_back(std::make_pair(i, y));
//    }
//    for (int i = x + 1; i < 8; ++i) {
//        if (jeuEchec->getCase(i, y)->getPiece() == nullptr)
//        {
//            if (jeuEchec->getCase(i, y)->getPiece()->getCouleur() == caseJeu->getCouleur())
//                break;
//            else
//            {
//                positions.push_back(std::make_pair(i, y));
//            }
//        }
//        else
//            positions.push_back(std::make_pair(i, y));
//    }
//
//    for (int j = y - 1; j >= 0; --j) {
//        if (jeuEchec->getCase(x, j)->getPiece() == nullptr)
//        {
//            if (jeuEchec->getCase(x, j)->getPiece()->getCouleur() == caseJeu->getCouleur())
//                break;
//            else
//            {
//                positions.push_back(std::make_pair(x, j));
//            }
//        }
//        else
//            positions.push_back(std::make_pair(x, j));
//    }
//
//    for (int j = y + 1; j < 8; ++j) {
//        if (jeuEchec->getCase(x, j)->getPiece() == nullptr)
//        {
//            if (jeuEchec->getCase(x, j)->getPiece()->getCouleur() == caseJeu->getCouleur())
//                break;
//            else
//            {
//                positions.push_back(std::make_pair(x, j));
//            }
//        }
//        else
//            positions.push_back(std::make_pair(x, j));
//    }
//			
//	return positions;
//}
