#pragma once
#include<vector>
#include<iostream>
#include "CellType.h"

#include "../headers/Point.h"

class Actor
{

public:
	std::vector<Point> PathToTarget;
	CellType Cell;
};

