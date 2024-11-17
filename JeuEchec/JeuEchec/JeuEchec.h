
#pragma once
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QGridLayout>
#include "ui_JeuEchec.h"
#include "cavalier.h"
#include "dame.h"
#include "fou.h"
#include "dame.h"
#include "roi.h"
#include "tour.h"
#include "case.h"
#include <QLabel>
#include "exceptions.hpp"
#include <QDir>

namespace controlleur {

    class JeuEchecControlleur
    {
    public:
        void initialiser();
        void resetPartie();

        void selectPiece(std::shared_ptr<Pieces> piece) { selectedPiece_ = piece; }
        void selectCase(std::shared_ptr<CaseControlleur> caseSel) { selectedCase_ = caseSel; }
        void resetSelection() { selectedPiece_ = nullptr; selectedCase_ = nullptr; }

        bool bougerPiece(int x, int y, int x2, int y2, int cas);
        void ajouterPiece(Type type, Couleur couleur, std::shared_ptr<CaseControlleur> caseJeu, int x, int y);

        std::shared_ptr<Pieces> getSelectedPiece() { return selectedPiece_; }
        std::shared_ptr<CaseControlleur> getSelectedCase() { return selectedCase_; }
        std::vector<std::pair<int, int>> genererMouvement(int x, int y);

        void setCases(std::shared_ptr<CaseControlleur> cases[8][8]);
        std::shared_ptr<CaseControlleur> getCase(int x, int y) { return cases_[x][y]; }
    

        std::vector<std::pair<int, int>> getPositions() { return positions_; }
		void setPositions(std::vector<std::pair<int, int>> positions) { positions_ = positions; }
        bool mouvementValide(int x, int y, int x2, int y2);

        bool pieceDejaSelectionne() { return selectedPiece_ != nullptr; }

        void clearPositions() { positions_.clear(); }

        void changerJoueur() { joueur_ = (joueur_ == Couleur::Blanc) ? Couleur::Noir : Couleur::Blanc; }
        Couleur getJoueur() { return joueur_; }

        Couleur mouvementEnEchec(int ancien_x, int ancien_y, const std::pair<int, int> pos);

        void verifierRois();
        bool isKingUnderAttack(int king_x, int king_y, Couleur kingColor);
		void setEchec(Couleur echec) { enEchec = echec; }
		Couleur getEchec() { return enEchec; }



    private:
        std::vector<std::pair<int, int>> positions_;
        std::shared_ptr<CaseControlleur> selectedCase_ = nullptr;
        std::shared_ptr<Pieces> selectedPiece_ = nullptr;
        std::shared_ptr<CaseControlleur> cases_[8][8];
        Couleur joueur_ = Couleur::Blanc;
        static int compteRoi_;
		Couleur enEchec = Couleur::Vide;
    };
}
 