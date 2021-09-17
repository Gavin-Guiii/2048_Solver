#include "Expectimax.h"
#include "Board.h"
#include <cmath>
#include <stdlib.h>

// Recursively evaluate which is the best move 
int Expectimax::expectimax(Board now, int depth, bool flag)
{
    if (depth == 0)
    {
        if (now.IsOver())
            return -1;
        else
            return CalEval(now);
    }

    if (flag)
    {
        int best = -1;
        for (int i = 0; i < 4; i++)
        {
            Board next = now;
            if (!next.MoveTo(i + 1))
                continue;

            int eval = expectimax(next, depth - 1, 0);
            if (eval > best)
                best = eval;
        }
        return best;
    }

    else
    {
        int sum_eval = 0, count = 0;
        for (int p = 0; p < 4; p++)
            for (int q = 0; q < 4; q++)
            {
                Board next = now;
                if (next.GetGrid(p, q)!= 0)
                    continue;

                next.SetGrid(p, q, 2);
                sum_eval += expectimax(next, depth - 1, 1);
                count++;
            }
        if (!count)
            return expectimax(now, depth - 1, 1);

        return sum_eval / count;
    }
}

// Return the best move
int Expectimax::BestMove(Board now, int depth)
{
    int best = -1, action = 0;

    for (int i = 0; i < 4; i++)
    {
        Board next = now;
        if (!next.MoveTo(i + 1))
            continue;

        int eval = expectimax(next, depth - 1, 0);
        if (eval > best)
        {
            best = eval;
            action = i + 1;
        }
    }

    return action;
}

// Calculate overall evaluation heuristics
int Expectimax::CalEval(Board now)
{
    return CalWeight(now) - CalCluster(now) + now.GetScore() + CalFree(now) * CalFree(now);
}

// Calculate weight heuristics
int Expectimax::CalWeight(Board now)
{
    int w = 0;
    int weight[4][4] = { 0, 0, 1, 3, 0, 1, 3, 5, 1, 3, 5, 15, 3, 5, 15, 30 };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            w += now.GetGrid(i, j) * weight[i][j];
    return w / 16;
}

// Calculate cluster heuristics
int Expectimax::CalCluster(Board now)
{
    int p = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int h = -1; h <= 1; h++)
                for (int k = -1; k <= 1; k++)
                {
                    if (i + h > 3 || i + h < 0 || j + k > 3 || j + k < 0)
                        continue;
                    p += abs(now.GetGrid(i + h, j + k) - now.GetGrid(i, j));
                }
    return p / 2;
}

// Calculate mono heuristics
int Expectimax::CalMono(Board now)
{
    int m = 0;
    for (int i = 1; i < 4; i++)
    {
        if (now.GetGrid(3, i - 1) == 0)
            continue;
        m += (now.GetGrid(3, i) / now.GetGrid(3, i - 1) == 2);
    }

    for (int i = 1; i < 4; i++)
    {
        if (now.GetGrid(i - 1, 3) == 0)
            continue;
        m += (now.GetGrid(i, 3) / now.GetGrid(i - 1, 3) == 2);
    }

    return m * 20;
}

// Return the number of empty tiles
int Expectimax::CalFree(Board now)
{
    int f = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!now.GetGrid(i,j))
                f++;
    return f;
}
