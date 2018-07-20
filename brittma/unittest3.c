/***************************************************
 * 
 *      Assignment 3: Unit Test #3
 *      Author: Matt Britt
 *      Date: July 19th, 2018
 *      Description:  This is a unit test for scoreFor().
 *  
 * *************************************************/

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

  struct gameState state;

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


void zeroDecks(int player)
{
      // init all deck to nothing

      for(int i = 0; i < MAX_HAND; i++)
        state.hand[player][i] = 100;
      
      for(int i = 0; i < MAX_DECK; i++)
        state.deck[player][i] = 100;

      for(int i = 0; i < MAX_DECK; i++)
        state.discard[player][i] = 100;
}

int runThrough(int player, int *array, int limit)
{
  int passCount = 0;
  int result;
      zeroDecks(player);

      printf("testing non scoring -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 0); 

      array[2] = curse;
      printf("testing 1 curse -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == -1);

      array[2] = estate;
      printf("testing 1 estate -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 1);

      array[2] = duchy;
      printf("testing 1 duchy -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 3);

      array[2] = province;
      printf("testing 1 province -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 6);

      array[2] = great_hall;
      printf("testing 1 great hall -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 1);


      for(int i = 0; i < 37; i++)
        array[i] = sea_hag;
      array[2] = gardens;
      state.deckCount[player] = 37;
      printf("testing 1  gardens -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 3);
 
   

      zeroDecks(player);

      array[0] = curse;
      array[2] = great_hall;
      printf("testing 1 curse & great hall -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 0);

      array[1] = estate;
      array[3] = duchy;
      array[4] = province;

      printf("testing 1 curse, estate, duchy, province, great hall -- ");
      result = scoreFor(player, &state);
      passCount += asserttrue(result == 10);


    return passCount;
}



// test function for scoreFor
void testScoreFor()
{
    const int numTests = 54;
    int passCount = 0;

    // init test State

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &state);
   // int result;
    for(int player = 0; player < 2; player++)
    {
      printf("\nTesting player %d, hand: \n\n", player );
      passCount += runThrough(player, state.hand[player], state.handCount[player]);
      
      printf("\nTesting player %d, deck: \n\n", player );
      passCount += runThrough(player, state.deck[player], state.deckCount[player]);
 
      endTurn(&state);

      state.discardCount[player] = 20;
      printf("\nTesting player %d, discard: \n\n", player );
      passCount += runThrough(player, state.discard[player], state.discardCount[player]);
 
    }

    // overall results
    printf("FINAL TEST RESULTS: %d / %d  ", passCount, numTests);
    asserttrue(passCount == numTests);


}


int main(int argc, char *argv[])
{
    testScoreFor();
    return 0;
}