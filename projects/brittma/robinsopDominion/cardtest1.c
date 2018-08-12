/***************************************************
 * 
 *      Assignment 3: Card Test #1
 *      Author: Matt Britt
 *      Date: July 20th, 2018
 *      Description:  This is a unit test for Smithy
 * 
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


void addSmithy(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = smithy;
    state->handCount[player]++;
}



void testSmithy()
{
    const int numTests = 2;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;

    addSmithy(0, &state);

    int originalHandSize = state.handCount[0];
    int originalNumSmithy = fullDeckCount(0, smithy, &state);

    int handPos = 0;
    for(handPos = 0; handPos < state.handCount[0]; handPos++)
        if(state.hand[0][handPos] == smithy)
            break;

    int bonus = 0;
    cardEffect(smithy, 0, 0, 0, &state, handPos, &bonus);

    printf("Testing 3 cards drawn");
    // plus 3 cards minus 1 smithy == original size plus 2
    passCount += asserttrue(state.handCount[0] == originalHandSize + 2);

    printf("Testing 1 fewer Smithy");
    int newNumSmithy = fullDeckCount(0, smithy, &state);
    passCount += asserttrue(newNumSmithy == originalNumSmithy - 1);

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);
}

int main()
{
    testSmithy();
    return 0;
}