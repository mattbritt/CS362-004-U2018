/**************************************************
 * 
 * Assignment 4: randomtestcard1
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  Random tester for the Smithy Dominion card.
 * 
 * ***********************************************/

#define NOISY_TEST 0

#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
//#include "dominion.c"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// count smithy cards from given array
int smithyCount(int array[], int size)
{
    int count = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == smithy) count++;

    return count;
}

// verify smithy played correctly
void checkSmithy(int currentPlayer, struct gameState *state, int handPos)
{
    int oSmithyCount = smithyCount(state->hand[currentPlayer], state->handCount[currentPlayer]);
    int oHandSize = state->handCount[currentPlayer];
    int oPlayedCardSize = state->playedCardCount;

    // check that playSmithy returned 0 (success)
    if(0 == asserttrue(playSmithy(currentPlayer, state, handPos) == 0))
    {
        printf("playSmithy() returned failure.\n");
    }

    // check that hand has 2 more cards (draw 3, discard the smithy)
    if(0 == asserttrue(oHandSize == state->handCount[currentPlayer] - 2))
    {
        printf("hand size not 2 greater than original hand size: oHandSize: %d -- handSize: %d\n", oHandSize, state->handCount[currentPlayer]);
    }

    // check that playedCardSize has incremented by 1 (smithy was played)
    if(0 == asserttrue(oPlayedCardSize == state->playedCardCount - 1))
    {
        printf("played card count not 1 greater than original count: oPlayedCardCount: %d -- playedCardCount: %d\n", oPlayedCardSize, state->playedCardCount);
    }

    // check that there is one less smithy in the hand
    if(0 == asserttrue(oSmithyCount == smithyCount(state->hand[currentPlayer], state->handCount[currentPlayer]) + 1))
    {
        printf("hand does not have 1 fewer smithy: oSmithyCount: %d -- smithyCount: %d\n", oSmithyCount, smithyCount(state->hand[currentPlayer], state->handCount[currentPlayer]));
    }


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

    printf("\n\n Testing Smithy . . .\n\n");

    randTestSmithy();
    return 0;
}