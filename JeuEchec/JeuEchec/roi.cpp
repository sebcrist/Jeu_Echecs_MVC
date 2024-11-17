#include "roi.h"

bool Roi::mouvementValide(int x, int y) const
{
	if (abs(x - this->getX()) <= 1 && abs(y - this->getY()) <= 1)
	{
		return true;
	}
	else
		return false;
}