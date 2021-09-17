#pragma once
#include "Board.h"

class Expectimax
{
public:
	// Return the best move
	int BestMove(Board, int);

	// Return the number of empty tiles
	int CalFree(Board);

private:
	// Recursively evaluate which is the best move 
	int expectimax(Board, int, bool);

	// Calculate overall evaluation heuristics
	int CalEval(Board);

	// Calculate weight heuristics
	int CalWeight(Board);

	// Calculate cluster heuristics
	int CalCluster(Board);

	// Calculate monotony heuristics
	// However, it is abandoned in the final version
	int CalMono(Board);
};

