#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Board.h"
#include "Expectimax.h"

using namespace std;

int main()
{
    // Set the rand seed
    srand(time(NULL));

    Board bd;
    Expectimax solver;

    // Repeatedly find the best move
    while (true)
    {
        bd.Display();

        // The search depth is related to the number of free tiles to reduce time
        int depth;
        if (solver.CalFree(bd) <= 4)
            depth = 6;
        else
            depth = 5;

        // Do the best move
        int action = solver.BestMove(bd, depth);
        if (action == 0)
            action = rand() % 4 + 1;
        bd.MoveTo(action);

        // If the game is over or player has won, end it
        if (bd.IsOver())
        {
            bd.Display();
            cout << "Final Score: " << bd.GetScore() << endl;
            cout << "Game Over!" << endl;
            return 0;
        }
        if (bd.IsWin())
        {
            bd.Display();
            cout << "Final Score: " << bd.GetScore() << endl;
            cout << "Win!" << endl;
            return 1;
        }
    }
    return -1;
}
