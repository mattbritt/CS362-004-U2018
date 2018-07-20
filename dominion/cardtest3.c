/***************************************************
 * 
 *      Assignment 3: Card Test #3
 *      Author: Matt Britt
 *      Date: July 20th, 2018
 *      Description:  This is a unit test for Baron
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


void addBaron(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = baron;
    state->handCount[player]++;
}



void testBaron()
{
    const int numTests = 2;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;

    addBaron(0, &state);

    int originalHandSize = state.handCount[0];
    int originalNumBaron = 0;

    for(int i = 0; i < state.handCount[0]; i++)
        if(state.hand[0][i] == baron)
            originalNumBaron++;

    int handPos = 0;
    for(handPos = 0; handPos < state.handCount[0]; handPos++)
        if(state.hand[0][handPos] == baron)
            break;

    int bonus = 0;
    cardEffect(baron, 0, 0, 0, &state, handPos, &bonus);

    int newNumBaron = 0;
    for(int i = 0; i < state.handCount[0]; i++)
        if(state.hand[0][i] == baron)
            newNumBaron++;

    printf("Testing 1 fewer Baron");
    passCount += asserttrue(newNumBaron == originalNumBaron - 1);
    printf("%d vs %d\n", newNumBaron, originalNumBaron);

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);
}

int main()
{
    testBaron();
    return 0;
}