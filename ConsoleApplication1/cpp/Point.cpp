#include "../headers/Point.h"

Point::Point()
{
	Row = -1;
	Coll = -1;
}

Point::Point(int row, int coll)
{
	Row = row;
	Coll = coll;
}
