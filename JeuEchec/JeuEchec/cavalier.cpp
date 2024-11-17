#include "cavalier.h"

bool Cavalier::mouvementValide(int x, int y) const
{
	if ((abs(x - this->getX()) == 2 && abs(y - this->getY()) == 1) || (abs(x - this->getX()) == 1 && abs(y - this->getY()) == 2))
	{
		return true;
	}
	else
		return false;
}