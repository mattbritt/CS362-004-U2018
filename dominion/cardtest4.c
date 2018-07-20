/***************************************************
 * 
 *      Assignment 3: Card Test #4
 *      Author: Matt Britt
 *      Date: July 20th, 2018
 *      Description:  This is a unit test for Feast
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


void addFeast(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = feast;
    state->handCount[player]++;
}



void testFeast()
{
    const int numTests = 3;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;
    int oDiscardCount = state.discardCount[0];
    addFeast(0, &state);

    int originalHandSize = state.handCount[0];
    
    int originalNumFeast = fullDeckCount(0, feast, &state);

    int handPos = 0;
    for(handPos = 0; handPos < state.handCount[0]; handPos++)
        if(state.hand[0][handPos] == feast)
            break;



    int bonus = 0;
    cardEffect(feast, 0, 0, 0, &state, handPos, &bonus);

    //endTurn(&state);

    printf("Testing 1 fewer Feast");
    int newNumFeast = fullDeckCount(0, feast, &state);
    passCount += asserttrue(newNumFeast == originalNumFeast - 1);
//printf("%d vs %d\n", originalNumFeast, newNumFeast);
    // overall results

    printf("Testing Discard card count++");
    passCount += asserttrue(state.discardCount[0] == oDiscardCount + 1);

    printf("Testing Discard card worth <= 5 coins");
    int cost = getCost(state.discard[0][state.discardCount[0]]);
    passCount += asserttrue(cost <= 5 && cost >= 0);



    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);
}

int main()
{
    testFeast();
    return 0;
}