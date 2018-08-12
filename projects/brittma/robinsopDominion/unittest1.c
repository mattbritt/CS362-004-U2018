/***************************************************
 * 
 *      Assignment 3: Unit Test #1
 *      Author: Matt Britt
 *      Date: July 19th, 2018
 *      Description:  This is a unit test for numHandCards().  This is a simple test to make sure my test framework is working.
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
    const int numTests = 3;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int result = initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;

    // test that initializeGame was successful
    printf("testing initializeGame -- ");
    passCount += asserttrue(result == 0);   

    // test that player 1 handCount is valid
    printf("testing state.handcount[0] {%d} == NumHandCards -- ", state.handCount[0]);
    passCount += asserttrue(state.handCount[0] == numHandCards(&state));

    // test player 2 handCount is valid
    state.whoseTurn = 1;

    printf("testing state.handcount[1] {%d} == NumHandCards -- ", state.handCount[1]);
    passCount += asserttrue(state.handCount[1] == numHandCards(&state));
    
    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);


}


int main(int argc, char *argv[])
{
    testNumHandCards();
    return 0;
}