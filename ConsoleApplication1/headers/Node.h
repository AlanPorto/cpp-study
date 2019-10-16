#pragma once
#include "Point.h"

struct Node
{
	Node(Point p)
	{
		ParentNode = nullptr;
		Position = p;
		CostF = 0;
		CostG = 0;
		CostH = 0;
	}

	Node* ParentNode;
	Point Position;

	int CostF;
	int CostG;
	int CostH;
};