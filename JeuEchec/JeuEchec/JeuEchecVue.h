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
#include "JeuEchec.h"

namespace vue
{
    class JeuEchecVue : public QMainWindow
    {
        Q_OBJECT

    public:
        JeuEchecVue(QWidget* parent = nullptr);
        ~JeuEchecVue();

        void selectionnerPartie(controlleur::JeuEchecControlleur* jeuEchec);
        void initialiser(controlleur::JeuEchecControlleur* jeuEchec);
        void resetPartie(controlleur::JeuEchecControlleur* jeuEchec);

        void ajouterPiece(controlleur::JeuEchecControlleur* jeuEchec, Type piece, Couleur couleur, int x, int y);
        void bougerPiece(controlleur::JeuEchecControlleur* jeuEchec, int x, int y, int x2, int y2, int cas);

        void selectionnerCase(controlleur::JeuEchecControlleur* jeuEchec, int x, int y);
        void remettreCouleur(controlleur::JeuEchecControlleur* jeuEchec);

        void setCases(controlleur::JeuEchecControlleur* jeuEchec, CaseVue* cases[8][8]);
        CaseVue* getCase(int x, int y) { return cases_[x][y]; }



    private:
        Ui::JeuEchecClass ui;
        CaseVue* cases_[8][8];
        int jeuSelectionne = 0;
        bool partieDemarree = false;
        QLabel* messages = nullptr;
    };
}