#include "Location.h"

bool Location::operator==(Location loc)
{
	return this->x == loc.x&&this->y == loc.y;
}
