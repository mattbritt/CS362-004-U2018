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



int testBaron(int choice)
{
   

    // init game data
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);

    // number of passing tests
    int passCount = 0;

    addBaron(0, &state);

    //int originalHandSize = state.handCount[0];
    int originalNumBaron = 0;

    for(int i = 0; i < state.handCount[0]; i++)
        if(state.hand[0][i] == baron)
            originalNumBaron++;

    int handPos = 0;
    for(handPos = 0; handPos < state.handCount[0]; handPos++)
        if(state.hand[0][handPos] == baron)
            break;


    int oNumEstates = fullDeckCount(0, estate, &state);
    int oCoins = state.coins;

    printf("choice == %d:\n", choice);
    int bonus = 0;
    cardEffect(baron, choice, 0, 0, &state, handPos, &bonus);
    int coinsGained = state.coins - oCoins;
    endTurn(&state);
    int newNumBaron = 0;
    for(int i = 0; i < state.handCount[0]; i++)
        if(state.hand[0][i] == baron)
            newNumBaron++;

    printf("Testing 1 fewer Baron");
    passCount += asserttrue(newNumBaron == originalNumBaron - 1);
   // printf("%d vs %d\n", newNumBaron, originalNumBaron);

    printf("Testing Discard estate for 4 coin OR gain estate");
    int newNumEstates = fullDeckCount(0, estate, &state);
    
    
    int estatesGained = newNumEstates - oNumEstates;

    passCount += asserttrue((estatesGained == 1) || (estatesGained == 0 && coinsGained == 4));
    //printf("%d vs %d\n", estatesGained, coinsGained);

    return passCount;


}

int main()
{
    int numTests = 4;

    int passCount = testBaron(0);
    passCount += testBaron(1);

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);

    return 0;
}