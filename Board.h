#pragma once
class Board
{
public:
    // Constructor
    Board();

    // Initialize the board
    void Init();

    // Add a 2 or 4 to the board
    void Add();

    // Display the board
    void Display();

    // Handle player's move
    bool MoveTo(int);

    // Return whether the board is full
    bool IsFull();

    // Return whether player has won
    bool IsWin();

    // Return whether the game is over
    int IsOver();

    // Return the score
    int GetScore();

    // Return the grid value
    int GetGrid(int, int);

    // Set the grid value
    void SetGrid(int, int, int);

private:
    // Move the tiles when possible
    void MoveTiles(int);

    // Merge two tiles when possible
    void MergeTiles(int);

    // Get the maximum number on the board
    int GetMaxNumber();

    // Test whether a move will make a difference
    bool TestMove();

    // Backup the grid
    void Backup();

    // Restore the grid
    void Restore();

    // Private variables
    int score = 0;
    int grid[4][4];
    int backup_grid[4][4];
};

