/***************************************************
 * 
 *      Assignment 3: Unit Test #2
 *      Author: Matt Britt
 *      Date: July 19th, 2108
 *      Description:  This is a unit test for fullDeckCount().
 *  
 * *************************************************/

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

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


// test function for fullDeckCount
void testFullDeckCount()
{
    const int numTests = 13;
    int passCount = 0;

    // init test State
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    // test uninitialized deck 
    int result = fullDeckCount(0, 0, &state);
 
    printf("testing uninitialized deck -- ");
    passCount += asserttrue(result == 0); 

    printf("testing initialized deck -- ");
    initializeGame(2, k, 1, &state);
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 0); 

    printf("testing card at start of deck -- ");
    state.deck[0][0] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    printf("testing card in middle of deck -- ");
    state.deck[0][0] = 5;
    state.deck[0][state.deckCount[0] / 2] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    printf("testing card at end of deck -- ");
    state.deck[0][state.deckCount[0] / 2] = 5;
    state.deck[0][state.deckCount[0] - 1] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    state.deck[0][state.deckCount[0] - 1] = 5;

    printf("testing card at start of hand -- ");
    state.hand[0][0] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    printf("testing card in middle of hand -- ");
    state.hand[0][0] = 5;
    state.hand[0][state.deckCount[0] / 2] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    printf("testing card at end of hand -- ");
    state.hand[0][state.deckCount[0] / 2] = 5;
    state.hand[0][state.deckCount[0] - 1] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

    printf("testing card at start of  discard -- ");
    state.hand[0][state.handCount[0] - 1] = 5;
    state.discard[0][0] = 0;
    state.discardCount[0] = 1;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 

endTurn(&state);

    printf("testing card in middle of discard -- ");
 
    state.discard[0][0] = 5;
    state.discard[0][state.discardCount[0] / 2] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 



    printf("testing card at end of  discard -- ");
 
    state.discard[0][state.discardCount[0] / 2] = 5;
    state.discard[0][state.discardCount[0] - 1] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 1); 


    printf("testing card in deck and discard -- ");
    state.deck[0][0] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 2); 

    printf("testing card in deck, hand and discard -- ");
    drawCard(0, &state);
    state.hand[0][0] = 0;
    result = fullDeckCount(0, 0, &state);
    passCount += asserttrue(result == 3); 

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);


}


int main(int argc, char *argv[])
{
    testFullDeckCount();
    return 0;
}