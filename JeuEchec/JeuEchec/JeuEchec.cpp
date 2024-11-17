#include "JeuEchec.h"

void controlleur::JeuEchecControlleur::initialiser() {

    std::shared_ptr<CaseControlleur> cases[8][8]{};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            auto caseJeu = std::make_shared<CaseControlleur>(CaseControlleur());

            if ((j % 2) == (i % 2))
            {
                caseJeu->setCouleur(Couleur::Blanc);
            }

            else
            {
                caseJeu->setCouleur(Couleur::Noir);
            }
            cases[i][j] = caseJeu;

        }
    }

    this->setCases(cases);

}




void controlleur::JeuEchecControlleur::resetPartie()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
			cases_[i][j]->setPiece(nullptr);
		}
	}
	compteRoi_ = 0;
}





void controlleur::JeuEchecControlleur::verifierRois() {
    if (compteRoi_ > 1) {
        throw MauvaisCompteRoiErreur("Avoir plus de deux rois est interdit");
    }
};

int controlleur::JeuEchecControlleur::compteRoi_ = 0;

void controlleur::JeuEchecControlleur::ajouterPiece(Type type, Couleur couleur, std::shared_ptr<CaseControlleur> caseJeu, int x, int y)
{
    if (type == Type::Tour)
    {
        auto tour = std::make_shared<Tour>(Tour(x, y, couleur));
        caseJeu->setPiece(tour);
    }
    else if (type == Type::Cavalier)
    {
        auto cavalier = std::make_shared<Cavalier>(Cavalier(x, y, couleur));
        caseJeu->setPiece(cavalier);
    }
    else if (type == Type::Fou)
    {
        auto fou = std::make_shared<Fou>(Fou(x, y, couleur));
        caseJeu->setPiece(fou);
    }
    else if (type == Type::Dame)
    {
        auto dame = std::make_shared<Dame>(Dame(x, y, couleur));
        caseJeu->setPiece(dame);
    }
    else if (type == Type::Roi)
    {
        auto roi = std::make_shared<Roi>(Roi(x, y, couleur));
        caseJeu->setPiece(roi);
    }
    else
    {
        // Empty
    }

}


bool controlleur::JeuEchecControlleur::mouvementValide(int x, int y, int x2, int y2)  {
    std::shared_ptr<CaseControlleur> fromCase = getCase(x, y);
    std::shared_ptr<CaseControlleur> toCase = getCase(x2, y2);

    if (toCase->getPiece() == nullptr)
    {
        if (fromCase->getPiece()->mouvementValide(x2, y2))
            return true;
        else
            return false;
    }
    else
    {
        if (fromCase->getPiece() ==nullptr)
			return false;
        if (fromCase->getPiece()->getCouleur() != toCase->getPiece()->getCouleur())
        {
            if (fromCase->getPiece()->mouvementValide(x2, y2))
                return true;
            else
                return false;
        }
            
        else
            return false;
    }

}





bool controlleur::JeuEchecControlleur::isKingUnderAttack(int king_x, int king_y, Couleur kingColor) {
    // Iterate through all opponent pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::shared_ptr<Pieces> piece = getCase(i, j)->getPiece();
            if (piece && piece->getCouleur() != kingColor) {
                // Found an opponent's piece
                std::vector<std::pair<int, int>> possibleMoves = genererMouvement(i, j);
                // Check if any possible move of the opponent's piece can attack the king
                for (const auto& move : possibleMoves) {
                    if (move.first == king_x && move.second == king_y) {
                        // The king is under attack
                        return true;
                    }
                }
            }
        }
    }
    // The king is not under attack
    return false;
}


Couleur controlleur::JeuEchecControlleur::mouvementEnEchec(int ancien_x, int ancien_y, std::pair<int, int> position) {
    Couleur vide = Couleur::Vide;

    // Save the original piece at the destination position
    std::shared_ptr<Pieces> originalPiece = getCase(position.first, position.second)->getPiece();
    std::shared_ptr<Pieces> pieceQuiBouge = getCase(ancien_x, ancien_y)->getPiece();

    // Simulate the move
    getCase(position.first, position.second)->setPiece(getCase(ancien_x, ancien_y)->getPiece());
    getCase(ancien_x, ancien_y)->setPiece(nullptr);

    // Check if any king is in check
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::shared_ptr<Pieces> piece = getCase(i, j)->getPiece();
            if (piece && piece->getType() == Type::Roi) {
                // Found a king
                Couleur kingColor = piece->getCouleur();
                // Check if the king is under attack
                if (isKingUnderAttack(i, j, kingColor)) {

                    if (pieceQuiBouge->getType() == Type::Roi) {
                        if (kingColor == joueur_) {
                            // The player's king is in check
                            // Restore the original state
                            getCase(ancien_x, ancien_y)->setPiece(getCase(position.first, position.second)->getPiece());
                            getCase(position.first, position.second)->setPiece(originalPiece);
                            // Return the color of the king in check
                            return kingColor;
                        }
                        else {
                            // The opponent's king is in check
                            // Restore the original state
                            getCase(ancien_x, ancien_y)->setPiece(getCase(position.first, position.second)->getPiece());
                            getCase(position.first, position.second)->setPiece(originalPiece);
                            // Return the color of the king in check
                            return joueur_;
                        }
                    }

                    // Restore the original state
                    getCase(ancien_x, ancien_y)->setPiece(getCase(position.first, position.second)->getPiece());
                    getCase(position.first, position.second)->setPiece(originalPiece);
                    // Return the color of the king in check
                    return kingColor;
                }
            }
        }
    }

    // Restore the original state
    getCase(ancien_x, ancien_y)->setPiece(getCase(position.first, position.second)->getPiece());
    getCase(position.first, position.second)->setPiece(originalPiece);

    return vide;
}



bool controlleur::JeuEchecControlleur::bougerPiece(int x, int y, int x2, int y2, int cas)
{
    if (mouvementValide(x, y, x2, y2))
    {
        std::shared_ptr<CaseControlleur> fromCase = getCase(x, y);
        std::shared_ptr<CaseControlleur> toCase = getCase(x2, y2);
        std::shared_ptr<Pieces> piece = fromCase->getPiece();
        piece->setXY(x2, y2);
        fromCase->setPiece(nullptr);
        toCase->setPiece(piece);
        if (cas == 1 || cas == 3)
        {
            enEchec = joueur_;
        }
        else if (cas == 2)
        {
			if (joueur_ == Couleur::Blanc)
                enEchec = Couleur::Noir;
            else
				enEchec = Couleur::Blanc;
		}
        else
			enEchec = Couleur::Vide;
        return true;
    }
    else
		return false;
 
}






std::vector<std::pair<int, int>> controlleur::JeuEchecControlleur::genererMouvement(int x, int y)
{
    std::shared_ptr<CaseControlleur> caseJeu = getCase(x, y);
    std::vector<std::pair<int, int>> positions;

    if (caseJeu->getPiece() == nullptr)
        return positions;

    Type type = caseJeu->getPiece()->getType();

    switch (type) {
    case Type::Tour: {

            for (int i = x - 1; i >= 0; i--) {
                if (getCase(i, y)->getPiece() != nullptr)
                {
                    if (getCase(i, y)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                        break;
                    else
                    {
                        positions.push_back(std::make_pair(i, y));
                        break;
                    }
                }
                else
                {
                    positions.push_back(std::make_pair(i, y));
                }
            }
            for (int i = x + 1; i < 8; i++) {
                if (getCase(i, y)->getPiece() != nullptr)
                {
                    if (getCase(i, y)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                        break;
                    else
                    {
                        positions.push_back(std::make_pair(i, y));
                        break;
                    }
                }
                else
                {
                    positions.push_back(std::make_pair(i, y));
                }
                    
            }

            for (int j = y - 1; j >= 0; j--) {
                if (getCase(x, j)->getPiece() != nullptr)
                {
                    if (getCase(x, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                        break;
                    else
                    {
                        positions.push_back(std::make_pair(x, j));
                        break;
                    }
                }
                else
                {
                    positions.push_back(std::make_pair(x, j));
                }
            }

            for (int j = y + 1; j < 8; j++) {
                if (getCase(x, j)->getPiece() != nullptr)
                {
                    if (getCase(x, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                        break;
                    else
                    {
                        positions.push_back(std::make_pair(x, j));
                        break;
                    }
                }
                else
                {
                    positions.push_back(std::make_pair(x, j));
                }
            }

        break;

    }
    case Type::Fou: {

        // Process bishop moves diagonally
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        break;
    }
    case Type::Dame: {
        // Process queen moves (combination of rook and bishop moves)

        // Rook-like moves
        for (int i = x - 1; i >= 0; i--) {
            if (getCase(i, y)->getPiece() != nullptr) {
                if (getCase(i, y)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, y));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, y));
            }
        }

        for (int i = x + 1; i < 8; i++) {
            if (getCase(i, y)->getPiece() != nullptr) {
                if (getCase(i, y)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, y));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, y));
            }
        }

        for (int j = y - 1; j >= 0; j--) {
            if (getCase(x, j)->getPiece() != nullptr) {
                if (getCase(x, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(x, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(x, j));
            }
        }

        for (int j = y + 1; j < 8; j++) {
            if (getCase(x, j)->getPiece() != nullptr) {
                if (getCase(x, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(x, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(x, j));
            }
        }

        // Bishop-like moves
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
            if (getCase(i, j)->getPiece() != nullptr) {
                if (getCase(i, j)->getPiece()->getCouleur() == caseJeu->getPiece()->getCouleur())
                    break;
                else {
                    positions.push_back(std::make_pair(i, j));
                    break;
                }
            }
            else {
                positions.push_back(std::make_pair(i, j));
            }
        }

        break;
    }
    case Type::Cavalier: {
        // Process knight moves
        std::vector<std::pair<int, int>> knightMoves = {
            {x - 2, y - 1}, {x - 2, y + 1}, {x - 1, y - 2}, {x - 1, y + 2},
            {x + 1, y - 2}, {x + 1, y + 2}, {x + 2, y - 1}, {x + 2, y + 1}
        };

        for (const auto& move : knightMoves) {
            int i = move.first;
            int j = move.second;
            if (i >= 0 && i < 8 && j >= 0 && j < 8) {
                if (getCase(i, j)->getPiece() == nullptr ||
                    getCase(i, j)->getPiece()->getCouleur() != caseJeu->getPiece()->getCouleur()) {
                    positions.push_back(move);
                }
            }
        }

        break;
    }
    case Type::Roi: {
        // Process king moves
        std::vector<std::pair<int, int>> kingMoves = {
            {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
            {x, y - 1},                 {x, y + 1},
            {x + 1, y - 1}, {x + 1, y}, {x + 1, y + 1}
        };

        for (const auto& move : kingMoves) {
            int i = move.first;
            int j = move.second;
            if (i >= 0 && i < 8 && j >= 0 && j < 8) {
                if (getCase(i, j)->getPiece() == nullptr ||
                    getCase(i, j)->getPiece()->getCouleur() != caseJeu->getPiece()->getCouleur()) {
                    positions.push_back(move);
                }
            }
        }

        break;
    }

    default:
        // Handle invalid type
        break;
    }
    return positions;
}
