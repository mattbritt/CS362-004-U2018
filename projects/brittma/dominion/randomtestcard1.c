/**************************************************
 * 
 * Assignment 4: randomtestcard1
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  Random tester for the Smithy Dominion card.
 * 
 * ***********************************************/

#define NOISY_TEST 1

#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion.c"
#include "rngs.h"
#include <stdio.h>


// verify smithy played correctly
void checkSmithy(int currentPlayer, struct gameState *state, int handPos)
{

    asserttrue(playSmithy(currentPlayer, state, handPos) == 0);


}

// add a Smithy card to hand
void addSmithy(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = smithy;
    state->handCount[player]++;
}

// random tester for Smithy Dominion card
void randTestSmithy()
{
    // init game data
    struct gameState *state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    //initializeGame(2, k, 1, &state);

    int p;
    
    for(int n = 0; n < 2000; n++)
    {

        state = newGame();

        // populate entire state with random data
        for(int i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)state)[i] = floor(Random() * 256);
        }
    
        // put valid random data in key state members
        p = floor(Random() * 2);
        state->deckCount[p] = floor(Random() * MAX_DECK);
        state->discardCount[p] = floor(Random() * MAX_DECK);
        state->handCount[p] = floor(Random() * MAX_HAND);
        state->playedCardCount = floor(Random() * MAX_HAND);
        addSmithy(p, state);
        checkSmithy(p, state, state->handCount[p] - 1);

        free(state);
    }




}

// test harness for smithy
int main()
{
    SelectStream(2);
    PutSeed(3);

    randTestSmithy();
    return 0;
}