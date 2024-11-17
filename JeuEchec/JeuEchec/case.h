#pragma once
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "pieces.h"

namespace controlleur
{
	class CaseControlleur
	{
	public:
		controlleur::CaseControlleur(std::shared_ptr<Pieces> piece = nullptr) { piece_ = piece; }
		~CaseControlleur() {}

		void setPiece(std::shared_ptr<Pieces> piece) { piece_ = piece; }
		std::shared_ptr<Pieces> getPiece() { return piece_; }
		void setCouleur(Couleur couleur) { couleur_ = couleur; }
		Couleur getCouleur() const { return couleur_; }



	private:
		std::shared_ptr<Pieces> piece_ = nullptr;
		bool caseSelectionnee_ = false;
		Couleur couleur_ = Couleur::Vide;

	};
}

namespace vue
{
	class CaseVue : public QPushButton
	{
		Q_OBJECT

	public:
		vue::CaseVue() {};
		void setCouleur(Couleur couleur) { couleur_ = couleur; }
		Couleur getCouleur() const { return couleur_; }
		~CaseVue() {};
	private:
		std::shared_ptr<Pieces> piece_ = nullptr;
		Couleur couleur_ = Couleur::Vide;
	};
}

