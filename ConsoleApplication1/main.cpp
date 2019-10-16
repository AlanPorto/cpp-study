#include <iostream>
#include "headers/Actor.h"
#include "headers/Maze.h"
#include "headers/Point.h"
#include "headers/CellType.h"
#include <string>

#pragma region Operator overload
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << p.Row << ", " << p.Coll;
	return os;
}

#pragma endregion

#define CLEAR_SCREEN() std::cout << std::string(50, '\n')

void InitGame(Maze& maze)
{
	maze.Init();
}

void ResetGame(Maze& maze, Actor& player, CellType& treasure)
{	
	maze.ResetMaze();
	maze.SetToOpenPosition(player.Cell);
	maze.SetToOpenPosition(treasure);

	maze.FindPath(player.Cell.Position, treasure.Position, player.PathToTarget);
}

int main()
{
	Maze maze;

	InitGame(maze);

	bool runGame = true;

	CellType treasure;
	treasure.SetType(kTreasureType);

	Actor player;
	player.Cell.SetType(kPlayerType);

	ResetGame(maze, player, treasure);

	while (runGame)
	{
		maze.PrintMaze(player.PathToTarget);
		std::cin.get();

		CLEAR_SCREEN();
		ResetGame(maze, player, treasure);
	}

	return 0;
}
