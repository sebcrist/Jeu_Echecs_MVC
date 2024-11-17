#include "dame.h"

bool Dame::mouvementValide(int x, int y) const
{
	if ((x == this->getX() || y == this->getY()) || (abs(x - this->getX()) == abs(y - this->getY())))
	{
		return true;
	}
	else
		return false;
}