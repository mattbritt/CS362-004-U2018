/***************************************************
 * 
 *      Assignment 3: Unit Test #4
 *      Author: Matt Britt
 *      Date: July 20th, 2018
 *      Description:  This is a unit test for whoseTurn().
 * 
 * 
 * *************************************************/

#include <stdio.h>
#include "dominion.h"

// asserttrue will output test results
int asserttrue(int test)
{
  if(test)
  {
    printf("-- TEST PASSED\n");
    return 1;
  }
  else
  {
    printf("-- *** TEST FAILED ***\n");
    return 0;
  }
}


// test function for numHandCards
void testNumHandCards()
{
    const int numTests = 2;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int result = initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;


    printf("testing whoseTurn player1 -- ");
    result = whoseTurn(&state);
    passCount += asserttrue(result == 0);   

    endTurn(&state);

    printf("testing whoseTurn player2 -- ");
    result = whoseTurn(&state);
    passCount += asserttrue(result == 1);

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);


}


int main(int argc, char *argv[])
{
    testNumHandCards();
    return 0;
}