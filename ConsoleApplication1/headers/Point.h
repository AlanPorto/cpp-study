#pragma once
struct Point
{
	short Row;
	short Coll;

	Point();
	Point(int row, int coll);

	inline int GetSqrDistance(Point b)
	{
		int deltaRow = Row - b.Row;
		int deltaColl = Coll - b.Coll;
		return (deltaRow * deltaRow) + (deltaColl * deltaColl);
	}

	bool operator==(Point other)
	{
		return (Row == other.Row) && (Coll == other.Coll);
	}
};
