#pragma once
#include <stdexcept>

class MauvaisCompteRoiErreur : public std::logic_error
{
public:
	using std::logic_error::logic_error;

};