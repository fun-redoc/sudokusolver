#ifdef __DEBUG__
#include <assert.h>
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h> // for RAND, and rand
#include <float.h>

#include <maybe.h>
#include <board.h>

#ifndef LEN
  #define LEN(a) ((sizeof a)/(sizeof *a))
#endif
#ifndef MIN
  #define MIN(a,b) (a<b?a:b)
#endif
#ifndef MAX
  #define MAX(a,b) (a>=b?a:b)
#endif

void some_tests()
{
  int raw1[] = { 0,0,0, 0,1,4, 0,0,0,
                 0,1,8, 3,0,0, 5,0,2, //<- 5 is fail row
                 0,7,2, 6,0,8, 0,0,0,

                 8,0,0, 2,0,0, 0,0,6,
                 1,0,3, 0,0,0, 8,9,0, //<- 1 is fail segment
                 0,6,1, 0,0,0, 0,4,1, //<- 1 is fail row

                 0,0,0, 0,0,0, 5,0,4,
                 0,0,0, 0,0,6, 0,0,0,
                 0,0,5, 0,7,3, 1,0,2};
  TBoard b1 = mkBoard(raw1);
  //printBoard(b1);
  assert(checkRow(b1,1));
  assert(checkRow(b1,2));
  assert(checkRow(b1,3));
  assert(checkRow(b1,4));
  assert(checkRow(b1,5));
  assert(!checkRow(b1,6));
  assert(checkRow(b1,7));
  assert(checkRow(b1,8));
  assert(checkRow(b1,9));
  assert(checkCol(b1,1));
  assert(checkCol(b1,2));
  assert(checkCol(b1,3));
  assert(checkCol(b1,4));
  assert(checkCol(b1,5));
  assert(checkCol(b1,6));
  assert(!checkCol(b1,7));
  assert(checkCol(b1,8));
  assert(!checkCol(b1,9));
  assert(checkSector(b1,1));
  assert(checkSector(b1,2));
  assert(checkSector(b1,3));
  assert(!checkSector(b1,4));
  assert(checkSector(b1,5));
  assert(checkSector(b1,6));
  assert(checkSector(b1,7));
  assert(checkSector(b1,8));
  assert(checkSector(b1,9));
  assert(!checkSector(b1,4));
  assert(!checkSector(b1,4));
  assert(!checkSector(b1,4));
  assert(!checkSector(b1,4));
  assert(!checkSector(b1,4));
  assert(!checkBoard(b1));
}

int examples[2][81] = {{0,0,0, 0,1,4, 0,0,0,
                     0,1,8, 3,0,0, 0,0,0,
                     0,7,2, 6,0,8, 0,0,0,

                     8,0,0, 2,0,0, 0,0,6,
                     0,0,3, 0,0,0, 8,9,0,
                     0,6,1, 0,0,0, 0,4,0,

                     0,0,0, 0,0,0, 5,0,4,
                     0,0,0, 0,0,6, 0,0,0,
                     0,0,5, 0,7,3, 1,0,2},

                    {1,0,0, 7,0,0, 6,0,0,
                     0,7,8, 3,0,4, 0,0,0,
                     3,0,0, 0,0,0, 0,0,0,

                     0,0,0, 0,0,0, 0,6,0,
                     6,0,0, 5,0,0, 0,0,7,
                     4,0,0, 0,0,0, 2,0,8,

                     0,0,4, 0,7,0, 8,1,0,
                     0,0,5, 8,1,0, 0,0,4,
                     0,3,0, 0,9,0, 0,0,0}
                 };
int main(void)
{
  some_tests();

  for(int i=0; i < LEN(examples); i++)
  {
    TBoard b = mkBoard(examples[i]);
    assert(checkBoard(b));
    printf("To solve:\n");
    printBoard(b);
    MAYBE(TBoard) solved = solve(b);
    if(IS_NOTHING2(solved))
    {
      printf("Board has no solution\n");
    }
    else
    {
      printf("solved:\n");
      printBoard(MAYBE_VALUE_ACCESS(solved));
    }
  }
}   
