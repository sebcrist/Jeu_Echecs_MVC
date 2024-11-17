#include "fou.h"

bool Fou::mouvementValide(int x, int y) const
{
	if (abs(x - this->getX()) == abs(y - this->getY()))
	{
		return true;
	}
	else
		return false;
}