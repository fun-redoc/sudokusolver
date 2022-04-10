#pragma clang diagnostic ignored "-Wextra-tokens" // i like terminatig endif with token
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "board.h"

#define ROW_SIZE 9
#define COL_SIZE 9
#define SECTOR_SIZE 3
#define NUM_SECTORS 9
#define BOARD_SIZE (ROW_SIZE*COL_SIZE)
#define FIELD_IDX(x,y) (y-1)*ROW_SIZE + (x-1)

TBoard mkBoard(int b[BOARD_SIZE])
{
    TBoard board;
    memcpy(board.board, b, 81*sizeof(int));
    return board;
}

int getField(TBoard b, int x, int y)
{
  assert(x >= 1 && x <= 9);
  assert(y >= 1 && y <= 9);
  return b.board[FIELD_IDX(x,y)];
}


void printBoard(TBoard b)
{
  for(int r=1; r<=ROW_SIZE; r++)
  {
    for(int c=1; c<=COL_SIZE; c++)
    {
      int x = getField(b, c, r);
#ifdef __DEBUG__        
        assert(x>=0 && x <=9);
#endif __DEBUG__
      printf("%1d", x);
      if(c % SECTOR_SIZE == 0){ printf(" ");}
    }
    printf("\n");
    if(r % SECTOR_SIZE == 0) { printf("\n");}
  }
}

bool checkRow(TBoard b, int r)
{
    bool res = true;
    int possibleVals[ROW_SIZE+1] = {0,1,2,3,4,5,6,7,8,9};
    int fromIdx = FIELD_IDX(1,r);
    int untilIdx = FIELD_IDX(1,r) + COL_SIZE - 1;

#ifdef __DEBUG__        
    int i=1;
    int dbg_c=0;
#endif __DEBUG__
    for(int c = fromIdx;
        res && c <= untilIdx;
        c++)
    {
        int x = b.board[c];
#ifdef __DEBUG__        
        assert(x>=0 && x <=9);
        assert(x == getField(b,i,r));
#endif __DEBUG__
        if(possibleVals[x] == x)  // unused field has same value
        {
           possibleVals[x] = 0; // mark field as used
        }
        else
        {
            res = false;
        }
#ifdef __DEBUG__
        assert(i<=ROW_SIZE);
        i++;
        dbg_c = c;
#endif __DEBUG_
    }
#ifdef __DEBUG__
    int lastField = FIELD_IDX(i,r);
    assert( lastField-1 == dbg_c);
#endif __DEBUG__
    return res;
}

bool checkCol(TBoard b, int c)
{
    int res = true;
    int possibleVals[COL_SIZE+1] = {0,1,2,3,4,5,6,7,8,9};
    int startIdx = FIELD_IDX(c,1);
    int lastIdx  = FIELD_IDX(c, 9);
    for(int i=startIdx; res && i <= lastIdx; i+=9)
    {
        int x = b.board[i];
        if(possibleVals[x] == x)
        {
            possibleVals[x] = 0;
        }
        else
        {
            res = false;
        }
    }
    return res;
}

bool checkSector(TBoard b, int s)
{
#ifdef __DEBUG__
    assert(s>=1 && s <= NUM_SECTORS);
#endif __DEBUG__
    bool res = true;
    int possibleVals[COL_SIZE+1] = {0,1,2,3,4,5,6,7,8,9};

    int sectColIdx = ((s-1)%3) * 3;
    int sectRow = ((s-1)/3)*3;
    int sectRowIdx = FIELD_IDX(1,sectRow+1);
    int firstIdx = sectRowIdx + sectColIdx;

    for(int secRow=0; res && secRow<SECTOR_SIZE; secRow++)
    {
        int curIdx = firstIdx;
        for(; res && curIdx<firstIdx+SECTOR_SIZE; curIdx++)
        {
            int x = b.board[curIdx];
            if(possibleVals[x] == x)
            {
                possibleVals[x] = 0;
            }
            else
            {
                res = false;
            }
        }
        firstIdx += ROW_SIZE;
    }
    return res;
}

bool checkBoard(TBoard b)
{
    bool res = true;
    for(int r=1; res && r<=ROW_SIZE; r++) 
    {
        res &= checkRow(b,r);
    }
    for(int c=1; res && c<=COL_SIZE; c++) 
    {
        res &= checkCol(b,c);
    }
    for(int s=1; res && s<=NUM_SECTORS; s++) 
    {
        res &= checkSector(b,s);
    }
    return res;
}

bool _solve_internal_rec(TBoard *b)
{
    bool res = checkBoard(*b);
    if(!res) 
    {
        return false;
    }
    else
    {
        for(int i=0; res && i<BOARD_SIZE; i++)
        {
            if(b->board[i] == 0)
            {
                bool found = false;
                for(int v=1; !found && v<=9; v++)
                {
                    b->board[i] = v; 
                    found = _solve_internal_rec(b);
                }
                if(!found)
                {
                    b->board[i] = 0; 
                    res = false;
                }
                else
                {
                    res = true;
                }
            }
        } 
        return res;
    }
}



MAYBE(TBoard) solve(TBoard b)
{
  TBoard copy_of_b = b;
  if(!_solve_internal_rec(&copy_of_b))
  {
      INIT_NOTHING(TBoard, resNothing);
      return resNothing;
  } 
  INIT_SOME(TBoard, resSome, copy_of_b);
  return resSome;
}
