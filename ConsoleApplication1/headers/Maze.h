#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include <stdlib.h> 

#include "Point.h"
#include "CellType.h"

class Maze
{
private:
	std::ifstream mFile;

	void GetRndOpenPosition(Point& point);

public:
	const int Rows = 31;
	const int Colls = 28;

	std::vector<std::vector<short>> MazeNumbers;

	void Init();
	void PrintMaze(std::vector<Point>& path);
	void ResetMaze();
	void SetToOpenPosition(CellType& cellType);
	bool FindPath(Point from, Point to, std::vector<Point>& path);
	bool IsPositionOpen(int row, int coll);
};

