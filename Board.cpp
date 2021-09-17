#include "Board.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>

using namespace std;

// Constructor
Board::Board()
{
    Init();
}

// Initialize the board
void Board::Init()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            grid[i][j] = 0;

    // Initally, the board should have two numbers
    Add();
    Add();
}

// Add a 2 or 4 to the board
void Board::Add()
{
    if (!IsFull())
    {
        int i = rand() % 4;
        int j = rand() % 4;
        int number_to_add = rand() % 100 < 90 ? 2 : 4;

        while (grid[i][j])
            i = rand() % 4, j = rand() % 4;
        grid[i][j] = number_to_add;
    }
}

// Display the board
void Board::Display()
{
    system("cls");
    cout << setw(52) << endl << endl << "AI Application -- 2048 Game" << endl << endl;
    cout << setw(50) << " |-----------------------|" << endl;

    for (int i = 0; i <= 3; i++)
    {
        cout << setw(24) << "";
        for (int j = 0; j <= 3; j++)
        {
            if (grid[i][j] == 0)
                cout << setw(2) << "|" << setw(4) << " ";
            else
                cout << setw(2) << "|" << setw(4) << grid[i][j];

            if (j == 3)
            {
                cout << setw(2) << "|" << endl;
                cout << setw(50) << " |-----------------------|" << endl;
            }
        }
    }
}

// Handle player's move
bool Board::MoveTo(int act)
{
    // Backup first, so that we can test whether a move is valid
    Backup();

    // Move->Merge->Move
    MoveTiles(act);
    MergeTiles(act);
    MoveTiles(act);

    // If the move is valid, add a new number to the board
    if (TestMove())
    {
        Add();
        return true;
    }
    else
    {
        return false;
    }
}

// Move the tiles when possible
void Board::MoveTiles(int act)
{
    switch (act)
    {
    case 1:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                if (!grid[j][i])
                    for (int k = j + 1; k <= 3; k++)
                        if (grid[k][i])
                        {
                            grid[j][i] = grid[k][i];
                            grid[k][i] = 0;
                            break;
                        }
        break;

    case 2:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j >= 0; j--)
                if (!grid[j][i])
                    for (int k = j - 1; k >= 0; k--)
                        if (grid[k][i])
                        {
                            grid[j][i] = grid[k][i];
                            grid[k][i] = 0;
                            break;
                        }
        break;

    case 3:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
                if (!grid[i][j])
                    for (int k = j + 1; k <= 3; k++)
                        if (grid[i][k])
                        {
                            grid[i][j] = grid[i][k];
                            grid[i][k] = 0;
                            break;
                        }
        break;

    case 4:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j >= 0; j--)
                if (!grid[i][j])
                    for (int k = j - 1; k >= 0; k--)
                        if (grid[i][k])
                        {
                            grid[i][j] = grid[i][k];
                            grid[i][k] = 0;
                            break;
                        }
        break;
    }
}

// Merge two tiles when possible
void Board::MergeTiles(int act)
{
    switch (act)
    {
    case 1:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[j][i] && grid[j][i] == grid[j + 1][i])
                {
                    grid[j][i] *= 2;
                    score += grid[j][i];
                    grid[j + 1][i] = 0;
                }
        break;

    case 2:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j > 0; j--)
                if (grid[j][i] && grid[j][i] == grid[j - 1][i])
                {
                    grid[j][i] *= 2;
                    score += grid[j][i];
                    grid[j - 1][i] = 0;
                }
        break;

    case 3:
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] && grid[i][j] == grid[i][j + 1])
                {
                    grid[i][j] *= 2;
                    score += grid[i][j];
                    grid[i][j + 1] = 0;
                }
        break;

    case 4:
        for (int i = 0; i <= 3; i++)
            for (int j = 3; j > 0; j--)
                if (grid[i][j] && grid[i][j] == grid[i][j - 1])
                {
                    grid[i][j] *= 2;
                    score += grid[i][j];
                    grid[i][j - 1] = 0;
                }
        break;
    }
}

// Test whether a move will make a difference
bool Board::TestMove()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (backup_grid[i][j] != grid[i][j])
                return 1;

    return 0;
}

// Get the maximum number on the board
int Board::GetMaxNumber()
{
    int m = 0;
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (grid[i][j] > m)
                m = grid[i][j];
    return m;
}

// Backup the grid
void Board::Backup()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            backup_grid[i][j] = grid[i][j];
}

// Restore the grid
void Board::Restore()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            grid[i][j] = backup_grid[i][j];
}

// Return whether the board is full
bool Board::IsFull()
{
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
            if (!grid[i][j])
                return 0;
    return 1;
}

// Return whether the game is over
int Board::IsOver()
{
    if (IsFull())
    {
        Backup();

        // Test whether all four directions are invalid
        for (int i = 1; i <= 4; i++)
            MergeTiles(i);

        bool flag = TestMove();
        Restore();
        if (!flag)
            return 1;
    }
    return 0;
}

// Return whether player has won
bool Board::IsWin()
{
    if (GetMaxNumber() == 2048)
        return 1;
    else
        return 0;
}

// Return the score
int Board::GetScore()
{
    return score;
}

// Return the grid value
int Board::GetGrid(int i, int j)
{
    return grid[i][j];
}

void Board::SetGrid(int i, int j, int value)
{
    grid[i][j] = value;
}
