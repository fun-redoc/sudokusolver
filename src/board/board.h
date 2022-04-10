#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdbool.h>
#include <maybe.h>

typedef struct 
{
    int board[81];
} TBoard;

MAYBE_TYPE(TBoard)

TBoard mkBoard(int b[81]);
int getField(TBoard b, int x, int y);
void printBoard(TBoard b);

bool checkRow(TBoard b, int r);
bool checkCol(TBoard b, int c);
bool checkSector(TBoard b, int s);
bool checkBoard(TBoard b);

MAYBE(TBoard) solve(TBoard b);


#endif
