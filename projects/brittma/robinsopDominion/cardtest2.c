/***************************************************
 * 
 *      Assignment 3: Card Test #2
 *      Author: Matt Britt
 *      Date: July 20th, 2018
 *      Description:  This is a unit test for Adventurer
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


void addAdventurer(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = adventurer;
    state->handCount[player]++;
}

int countTreasure(int* array, int max)
{
    int treasureCount = 0;
    for(int i = 0; i < max; i++)
    {
        if(array[i] == copper || array[i] == silver || array[i] == gold)
            treasureCount++;
    }

return treasureCount;
}

void testAdventurer()
{
    const int numTests = 3;

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;

    state.deck[0][0] = copper;
    state.deck[0][1] = silver;
    state.deck[0][2] = sea_hag;

    state.deckCount[0] = 3;

    addAdventurer(0, &state);

    
    int originalNumAdventurer = fullDeckCount(0, adventurer, &state);
    int oTreasureCount = countTreasure(state.deck[0], state.deckCount[0]);
    int oDiscardCount = state.discardCount[0];
    int oDeckCount = state.deckCount[0];

    int handPos = 0;
    for(handPos = 0; handPos < state.handCount[0]; handPos++)
        if(state.hand[0][handPos] == adventurer)
            break;

    int bonus = 0;
    cardEffect(adventurer, 0, 0, 0, &state, handPos, &bonus);

    printf("Testing Found 2 Treasure OR all deck drawn");
    int found2Treasure = (countTreasure(state.deck[0], state.deckCount[0])) == oTreasureCount - 2;
    int allDeckDrawn = (state.deckCount[0] == 0);
    passCount += asserttrue(found2Treasure|| allDeckDrawn);

    printf("Testing 1 fewer Adventurer");
    int newNumAdventurer = fullDeckCount(0, smithy, &state);
    passCount += asserttrue(newNumAdventurer == originalNumAdventurer - 1);

    printf("Testing Discarded cards count");
    int discarded = state.discardCount[0] - oDiscardCount;
    int decked = oDeckCount - state.deckCount[0];
    passCount += asserttrue(discarded == decked - 2);
    printf("%d - %d ", discarded, decked);




    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);
}

int main()
{
    testAdventurer();

    return 0;
}