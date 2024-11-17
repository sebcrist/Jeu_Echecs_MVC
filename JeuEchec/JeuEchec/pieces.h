#pragma once
#include <map>
#include <string>
#include <iostream>
#include "vector"





enum class Couleur
{
	Blanc,
	Noir,
	Vide
};

enum class Type
{
	Roi,
	Dame,
	Tour,
	Cavalier,
	Fou,
	Vide
};

class Pieces
{
public:
	Pieces(int x = 0, int y = 0, Couleur couleur = Couleur::Vide, Type type = Type::Vide) { x_ = x; y_ = y; couleur_ = couleur; type_ = type; }
	~Pieces() {}

	int getX() const { return x_; }
	int getY() const { return y_; }

	Couleur getCouleur() const { return couleur_; }
	Type getType() const { return type_; }

	void setXY(int x, int y) { x_ = x; y_ = y; }
	virtual bool mouvementValide(int x, int y) const =0;


private:
	int x_;
	int y_;
	Couleur couleur_ = Couleur::Vide;
	Type type_ = Type::Vide;

};
