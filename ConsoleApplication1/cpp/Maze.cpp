#include "../headers/Maze.h"
#include <time.h> 
#include "../headers/Node.h"

void Maze::Init()
{
	srand(time(NULL));

	mFile.open("C:\\Users\\AlanPorto\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\Resources\\mazeTxt.txt");

	if (!mFile)
	{
		std::cout << "Unable to open file" << std::endl;
		return;
	}

	int colIndex = 0;

	std::vector<short> rowContent;

	while (!mFile.eof())
	{
		short cellType;
		mFile >> cellType;

		rowContent.push_back(cellType);

		colIndex++;

		if (colIndex >= Maze::Colls)
		{
			MazeNumbers.push_back(rowContent);
			rowContent.clear();
			colIndex = 0;
		}
	}
}

void Maze::PrintMaze(std::vector<Point>& path)
{
	for (int i = 0; i < Maze::Rows; i++)
	{
		std::vector<short> rowVec = MazeNumbers[i];
		for (int j = 0; j < Maze::Colls; j++)
		{
			char charToPrint;

			short cellType = rowVec[j];

			bool printingPath = false;

			if (cellType == kOpenPathType)
			{
				for (int k = 0; k < path.size(); k++)
				{
					Point p = path[k];
					if (p.Row == i && p.Coll == j)
					{
						charToPrint = '.';
						printingPath = true;

						path.erase(path.begin() + k);
						break;
					}
				}
			}

			if (!printingPath)
			{
				charToPrint = CellType::GetCharForType(cellType);
			}

			std::cout << charToPrint;
		}

		std::cout << std::endl;
	}
}

void Maze::ResetMaze()
{
	for (int i = 0; i < Maze::Rows; i++)
	{
		std::vector<short> rowVec = MazeNumbers[i];
		for (int j = 0; j < Maze::Colls; j++)
		{
			short cellType = rowVec[j];

			if ((cellType != kOpenPathType) && (cellType != kWallType))
			{
				MazeNumbers[i][j] = kOpenPathType;
			}
		}
	}
}

void Maze::SetToOpenPosition(CellType& cellType)
{
	GetRndOpenPosition(cellType.Position);
	MazeNumbers[cellType.Position.Row][cellType.Position.Coll] = cellType.Type;
}

void Maze::GetRndOpenPosition(Point& point)
{
	short coll, row;

	do
	{
		row = rand() % Rows;
		coll = rand() % Colls;

	} while (MazeNumbers[row][coll] != 0);

	point.Row = row;
	point.Coll = coll;
}

bool Maze::IsPositionOpen(int row, int coll)
{
	if ((row < 0) || (row >= Maze::Rows) || (coll < 0) || (coll >= Maze::Colls))
	{
		return false;
	}

	return (MazeNumbers[row][coll] != kWallType);
}

bool Maze::FindPath(Point from, Point to, std::vector<Point>& path)
{
	path.clear();

	Point directions[4] = { Point(0, -1), Point(0, 1), Point(-1, 0), Point(1, 0) }; // Down, Up, Left, Right

	Node* startNode = new Node(from);
	Node* endNode = new Node(to);

	std::vector<Node*> openNodes;
	openNodes.push_back(startNode);

	std::vector<Point> closedPoints;

	while (openNodes.size() > 0)
	{
		Node* currentNode = openNodes[0];
		int indexToRemove = 0;

		for (int i = 0; i < openNodes.size(); i++)
		{
			Node* openNode = openNodes[i];

			if (openNode->CostF < currentNode->CostF)
			{
				currentNode = openNode;
				indexToRemove = i;
			}
		}

		openNodes.erase(openNodes.begin() + indexToRemove);
		closedPoints.push_back(currentNode->Position);

		Point pointToTest = currentNode->Position;

		if (pointToTest == to)
		{
			Node* nextNode = currentNode;

			while (nextNode)
			{
				path.push_back(nextNode->Position);
				Node* parentNode = nextNode->ParentNode;
				nextNode = parentNode;
			}

			// TODO: Clear allocations here.
			// Found a path!
			return true;
		}

		std::vector<Node*> childrenNodes;

		for (int i = 0; i < 4; i++)
		{
			Point direction = directions[i];
			short candidateRow = currentNode->Position.Row + direction.Row;
			short candidateColl = currentNode->Position.Coll + direction.Coll;

			if (IsPositionOpen(candidateRow, candidateColl))
			{
				Point newPoint(candidateRow, candidateColl);
				Node* newNode = new Node(newPoint);
				newNode->ParentNode = currentNode;
				childrenNodes.push_back(newNode);
			}
		}

		for (int i = 0; i < childrenNodes.size(); i++)
		{
			Node* childNode = childrenNodes[i];

			bool skipNode = false;

			for (int j = 0; j < closedPoints.size(); j++)
			{
				if (childNode->Position == closedPoints[j])
				{
					skipNode = true;
					break;
				}
			}

			if (skipNode)
			{
				continue;
			}

			childNode->CostG = currentNode->CostG + 1;
			childNode->CostH = childNode->Position.GetSqrDistance(to);
			childNode->CostF = childNode->CostG + childNode->CostH;


			for (int j = 0; j < openNodes.size(); j++)
			{
				Node* openNode = openNodes[j];

				if (childNode->Position == openNode->Position && childNode->CostG > openNode->CostG)
				{
					skipNode = true;
					break;
				}
			}

			if (!skipNode)
			{
				openNodes.push_back(childNode);
			}
		}

	}

	// Fail to find a path
	delete[] directions;
	return false;
}