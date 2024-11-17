#include "JeuEchec.h"
#include "JeuEchecVue.h"

Couleur operator~(Couleur b) {
    if (b == Couleur::Blanc)
        return Couleur::Noir;
    else
        return Couleur::Blanc;
}

std::string colorToString(Couleur couleur)
{
    static const std::map<Couleur, std::string> typeMap = {
        {Couleur::Blanc, "blanc"},
        {Couleur::Noir, "noir"}
    };

    auto it = typeMap.find(couleur);
    if (it != typeMap.end())
    {
        return it->second;
    }
    else
    {
        return "NonConnu";
    }
}


std::string typeToString(Type type)
{
    static const std::map<Type, std::string> typeMap = {
        {Type::Cavalier, "cavalier"},
        {Type::Tour, "tour"},
        {Type::Fou, "fou"},
        {Type::Dame, "dame"},
        {Type::Roi, "roi"}
    };

    auto it = typeMap.find(type);
    if (it != typeMap.end())
    {
        return it->second;
    }
    else
    {
        return "NonConnu";
    }
}



void vue::JeuEchecVue::selectionnerPartie(controlleur::JeuEchecControlleur* jeuEchec)
{
    if (partieDemarree)
    {
        messages->setText("La partie est deja demarree \nAssurer vous de reset la partie");
        return;
    }



    if (jeuSelectionne == 0)
    {
        ajouterPiece(jeuEchec, Type::Roi, Couleur::Noir, 0, 3);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Noir, 1, 4);

        ajouterPiece(jeuEchec, Type::Roi, Couleur::Blanc, 2, 3);
        ajouterPiece(jeuEchec, Type::Fou, Couleur::Blanc, 3, 3);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Blanc, 7, 5);
        partieDemarree = true;
    }
    else if (jeuSelectionne == 1)
    {
        ajouterPiece(jeuEchec, Type::Roi, Couleur::Noir, 2, 5);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Noir, 3, 0);

        ajouterPiece(jeuEchec, Type::Roi, Couleur::Blanc, 4, 5);
        ajouterPiece(jeuEchec, Type::Fou, Couleur::Blanc, 4, 4);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Blanc, 6, 7);
        partieDemarree = true;
    }
    else if (jeuSelectionne == 2)
    {
        ajouterPiece(jeuEchec, Type::Roi, Couleur::Noir, 0, 2);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Noir, 7, 4);

        ajouterPiece(jeuEchec, Type::Roi, Couleur::Blanc, 2, 2);
        ajouterPiece(jeuEchec, Type::Fou, Couleur::Blanc, 5, 1);
        ajouterPiece(jeuEchec, Type::Tour, Couleur::Blanc, 1, 7);
        partieDemarree = true;
    }
    else
        return;

}


void vue::JeuEchecVue::initialiser(controlleur::JeuEchecControlleur* jeuEchec) {
    QGridLayout* mainWind = new QGridLayout();
    this->centralWidget()->setLayout(mainWind);

    QGridLayout* layoutJeu = new QGridLayout();
    QGridLayout* layoutInfo = new QGridLayout();
    mainWind->addLayout(layoutJeu, 0, 0);
    mainWind->addLayout(layoutInfo, 0, 1);

    mainWind->setColumnStretch(0, 3);
    mainWind->setColumnStretch(1, 1);

    CaseVue* casesVue[8][8]{};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            CaseVue* caseVue = new CaseVue();
            casesVue[i][j] = caseVue;
            caseVue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if ((j % 2) == (i % 2))
            {
                caseVue->setCouleur(Couleur::Blanc);
                caseVue->setStyleSheet("background-color: rgb(245, 229, 186)");
            }

            else
            {
                caseVue->setCouleur(Couleur::Noir);
                caseVue->setStyleSheet("background-color: rgb(41, 41, 41)");
            }

            layoutJeu->addWidget(caseVue, i, j);

        }
    }

    this->setCases(jeuEchec, casesVue);

    QListWidget* listWidget = new QListWidget();

    layoutInfo->addWidget(listWidget, 0, 0);

    QListWidgetItem* jeuAmu = new QListWidgetItem;
    jeuAmu->setText("The Cochrane defence");
    listWidget->insertItem(0, jeuAmu);

    QListWidgetItem* jeuEnn = new QListWidgetItem;
    jeuEnn->setText("The Philidor position");
    listWidget->insertItem(1, jeuEnn);

    QListWidgetItem* jeuEch = new QListWidgetItem;
    jeuEch->setText("Super Mise en echec");
    listWidget->insertItem(2, jeuEch);

    QLabel* label = new QLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    layoutInfo->addWidget(label, 1, 0);

    messages = label;

    QPushButton* demarrerPartie = new QPushButton("Demarrer une partie");
    demarrerPartie->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutInfo->addWidget(demarrerPartie, 2, 0);

    QPushButton* reset = new QPushButton("Reset");
    reset->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutInfo->addWidget(reset, 3, 0);

    QObject::connect(demarrerPartie, &QPushButton::clicked, [this, jeuEchec, listWidget]() {
        jeuSelectionne = listWidget->currentRow();
        selectionnerPartie(jeuEchec);
        listWidget->setCurrentRow(-1);
        messages->setText("Au tour des blanc");
        });

    QObject::connect(reset, &QPushButton::clicked, [this, jeuEchec]() {
        resetPartie(jeuEchec);
        });

    layoutInfo->setRowStretch(0, 2);
    layoutInfo->setRowStretch(1, 2);
    layoutInfo->setRowStretch(2, 1);
    layoutInfo->setRowStretch(3, 1);
}

void vue::JeuEchecVue::resetPartie(controlleur::JeuEchecControlleur* jeuEchec)
{
    if (!partieDemarree)
    {
        messages->setText("La partie n'a pas encore demarree");
        return;
    }
    partieDemarree = false;
    jeuSelectionne = -1;
    messages->setText("La partie a ete reset");
    jeuEchec->resetPartie();
    remettreCouleur(jeuEchec);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cases_[i][j]->setIcon(QIcon());
        }
    }
}

void vue::JeuEchecVue::remettreCouleur(controlleur::JeuEchecControlleur* jeuEchec)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            CaseVue* caseVue = getCase(i, j);
            std::shared_ptr<controlleur::CaseControlleur> caseJeu = jeuEchec->getCase(i, j);
            if (caseVue->getCouleur() == Couleur::Blanc)
                caseVue->setStyleSheet("background-color: rgb(245, 229, 186)");
            else
                caseVue->setStyleSheet("background-color: rgb(41, 41, 41)");

            if (caseJeu->getPiece() == nullptr)
            {

                caseVue->disconnect();
            }
            else
            {
                caseVue->disconnect();
                QObject::connect(this->cases_[i][j], &QPushButton::clicked, [this, jeuEchec, i, j]() {
                    selectionnerCase(jeuEchec, i, j);
                    });
            }

        }
    }
    jeuEchec->selectPiece(nullptr);
    jeuEchec->changerJoueur();
}

vue::JeuEchecVue::JeuEchecVue(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cases_[i][j] = nullptr;
        }
    }

}

vue::JeuEchecVue::~JeuEchecVue()
{}

void controlleur::JeuEchecControlleur::setCases(std::shared_ptr<CaseControlleur> cases[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->cases_[i][j] = cases[i][j];
        }
    }
}

void vue::JeuEchecVue::setCases(controlleur::JeuEchecControlleur* jeuEchec, CaseVue* cases[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->cases_[i][j] = cases[i][j];
            QObject::connect(this->cases_[i][j], &QPushButton::clicked, [this, jeuEchec, i, j]() {
                selectionnerCase(jeuEchec, i, j);
                });
        }
    }
}

void vue::JeuEchecVue::ajouterPiece(controlleur::JeuEchecControlleur* jeuEchec, Type piece, Couleur couleur, int x, int y)
{
    bool ok = true;
    /*try {
        jeuEchec->verifierRois();
        ok = true;
    }
    catch (MauvaisCompteRoiErreur& erreur) {

        std::cout << "Trop grand nombre de rois: " << erreur.what() << std::endl;
    }*/
    if (ok) {
        QDir pathPresent = QDir::current();
        QIcon icon;
        QString pathPiece = pathPresent.filePath(QString::fromStdString(typeToString(piece) + colorToString(couleur) + ".png"));
        icon.addFile(pathPiece);
        CaseVue* caseJeu = getCase(x, y);
        caseJeu->setIcon(icon);
        caseJeu->setIconSize(QSize(60, 60));
        caseJeu->disconnect();
        QObject::connect(caseJeu, &QPushButton::clicked, [this, jeuEchec, piece, couleur, x, y]() {
            selectionnerCase(jeuEchec, x, y);
            });

        jeuEchec->ajouterPiece(piece, couleur, jeuEchec->getCase(x, y), x, y);
    }
}


void vue::JeuEchecVue::bougerPiece(controlleur::JeuEchecControlleur* jeuEchec, int x, int y, int x2, int y2, int cas)
{
    if (jeuEchec->bougerPiece(x, y, x2, y2, cas))
    {
        switch (cas)
        {
        case 1:
            messages->setText(QString::fromStdString("Au tour des " + colorToString(~jeuEchec->getJoueur()) + "\n" + (colorToString(jeuEchec->getJoueur()) + " mis en echec")));
            break;
        case 2:
            messages->setText(QString::fromStdString("Au tour des " + colorToString(~jeuEchec->getJoueur()) + "\n" + (colorToString(~jeuEchec->getJoueur()) + " mis en echec")));
            break;
        default:
            messages->setText(QString::fromStdString("Au tour des " + (colorToString(~jeuEchec->getJoueur()))));
            break;
        }
        CaseVue* fromCase = getCase(x, y);
        CaseVue* toCase = getCase(x2, y2);
        QIcon icon = fromCase->icon();
        toCase->setIcon(icon);
        fromCase->setIcon(QIcon());
        toCase->setIconSize(QSize(60, 60));
        remettreCouleur(jeuEchec);
    }
    else
        return;

}

void vue::JeuEchecVue::selectionnerCase(controlleur::JeuEchecControlleur* jeuEchec, int x, int y)
{
    int cas = 0;
    CaseVue* caseJeu = getCase(x, y);

    if (jeuEchec->pieceDejaSelectionne()) {
        if (jeuEchec->getCase(x, y)->getPiece() == jeuEchec->getSelectedPiece())
        {
            jeuEchec->selectPiece(nullptr);
            remettreCouleur(jeuEchec);
            jeuEchec->changerJoueur();
            return;
        }
        else
        {
            std::cout << "Piece deja selectionne" << std::endl;
            return;
        }
    }
    else if (jeuEchec->getCase(x, y)->getPiece() == nullptr) {
        std::cout << "Case vide" << std::endl;
        return;
    }
    else if (jeuEchec->getJoueur() != jeuEchec->getCase(x, y)->getPiece()->getCouleur())
    {
        std::cout << "Couleur de joueur" << std::endl;
        return;
    }

    caseJeu->setStyleSheet("background-color: red");
    std::cout << "case a ete selectionne xy: " << x << " " << y << std::endl;

    jeuEchec->selectPiece(jeuEchec->getCase(x, y)->getPiece());
    jeuEchec->setPositions(jeuEchec->genererMouvement(x, y));

    for (const auto& position : jeuEchec->getPositions())
    {
        std::cout << "Pour le joueur : " << colorToString(jeuEchec->getJoueur()) << ", " << "Position: " << ": " << position.first << " " << position.second << " : ";
        Couleur couleur = jeuEchec->mouvementEnEchec(x, y, position);
        if (couleur == Couleur::Vide)
        {
            std::cout << "Pas dechec" << std::endl;
            cas = 0;
        }
        else if (couleur == jeuEchec->getJoueur())
        {
            std::cout << "Joueur est mis en echec" << std::endl;
            cas = 1;
            continue;
        }
        else if (couleur != jeuEchec->getJoueur())
        {
            std::shared_ptr<Pieces> originalPiece = jeuEchec->getCase(position.first, position.second)->getPiece();
            std::shared_ptr<Pieces> pieceQuiBouge = jeuEchec->getCase(x, y)->getPiece();

            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    std::shared_ptr<Pieces> piece = jeuEchec->getCase(i, j)->getPiece();
                    if (piece && piece->getType() == Type::Roi && piece->getCouleur() == jeuEchec->getJoueur()) {
                        // Found the player's king

                        // Simulate the move
                        jeuEchec->getCase(position.first, position.second)->setPiece(jeuEchec->getCase(x, y)->getPiece());
                        jeuEchec->getCase(x, y)->setPiece(nullptr);

                        if (jeuEchec->isKingUnderAttack(i, j, jeuEchec->getJoueur())) {
                            // The player's king is in check
                            std::cout << "Joueur mis en echec" << std::endl;
                            cas = 1;
                            break;
                        }
                        else {
                            std::cout << "Opponent mis en echec" << std::endl;
                            cas = 2;
                            break;
                        }

                    }
                }
            }
            jeuEchec->getCase(x, y)->setPiece(jeuEchec->getCase(position.first, position.second)->getPiece());
            jeuEchec->getCase(position.first, position.second)->setPiece(originalPiece);
            if (cas == 1)
            {
                continue;
            }
            else
            {
                cas = 2;
            }
        }

        int i = position.first;
        int j = position.second;

        CaseVue* caseJeu2 = getCase(i, j);
        caseJeu2->setStyleSheet("background-color: green");

        QObject::connect(caseJeu2, &QPushButton::clicked, [this, jeuEchec, x, y, i, j, cas]() {
            bougerPiece(jeuEchec, x, y, i, j, cas);
            });

    }
    jeuEchec->clearPositions();

}