#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>

#define ALIVE true
#define DEAD false

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}


const int gridsize = 75; //Making this a global constant to avoid array issues.

void Display(bool grid[gridsize + 1][gridsize + 1]) {
    for (int a = 1; a < gridsize; a++) {
        for (int b = 1; b < gridsize; b++) {
            if (grid[a][b] == true) {
                std::printf(" *");
            }
            else {
                std::printf("  ");
            }
            if (b == gridsize - 1) {
                std::printf("\n");
            }
        }
    }

    std::fflush(stdout);
}
//This copy's the grid for comparision purposes.
void CopyGrid(bool grid[gridsize + 1][gridsize + 1], bool grid2[gridsize + 1][gridsize + 1]) {
    for (int a = 0; a < gridsize; a++) {
        for (int b = 0; b < gridsize; b++) { grid2[a][b] = grid[a][b]; }
    }
}
//Calculates Life or Death
void liveOrDie(bool grid[gridsize + 1][gridsize + 1]) {
    bool grid2[gridsize + 1][gridsize + 1] = {};
    CopyGrid(grid, grid2);
    for (int a = 1; a < gridsize; a++) {
        for (int b = 1; b < gridsize; b++) {
            int neighbors = 0;
            for (int c = -1; c < 2; c++) {
                for (int d = -1; d < 2; d++) {
                    if (!(c == 0 && d == 0)) {
                        if (grid2[a + c][b + d]) { ++neighbors; }
                    }
                }
            }
            if (neighbors < 2) { grid[a][b] = DEAD; }
            else if (neighbors == 3) { grid[a][b] = ALIVE; }
            else if (neighbors > 3) { grid[a][b] = DEAD; }
        }
    }
}

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //const int gridsize = 50;
    bool grid[gridsize + 1][gridsize + 1] = {};

    //Still have to manually enter the starting cells.
    grid[gridsize / 2][gridsize / 2] = true;
    grid[gridsize / 2 - 1][gridsize / 2] = true;
    grid[gridsize / 2][gridsize / 2 + 1] = true;
    grid[gridsize / 2][gridsize / 2 - 1] = true;
    grid[gridsize / 2 + 1][gridsize / 2 + 1] = true;

    while (true) {
        //The following copies our grid.

        Display(grid);     //This is our display.
        liveOrDie(grid); //calculate if it lives or dies.
        ClearScreen();
    }
}