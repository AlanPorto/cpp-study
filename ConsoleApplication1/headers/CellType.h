#pragma once
#include "Point.h"

constexpr short kOpenPathType = 0;
constexpr short kWallType = 1;
constexpr short kPlayerType = 2;
constexpr short kTreasureType = 5;

struct CellType
{
	short Type;
	char Name;
	Point Position;

	inline void SetType(short type)
	{
		Type = type;
		Name = GetCharForType(Type);
	}
	
	static char GetCharForType(short type)
	{
		switch (type)
		{
			case kOpenPathType:
				return ' ';

			case kWallType:
				return '|';

			case kPlayerType:
				return 'P';

			case kTreasureType:
				return 'T';
		}

		return '?';
	}
};