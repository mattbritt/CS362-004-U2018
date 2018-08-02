/**************************************************
 * 
 * Assignment 4: randomtestcard2
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  Random tester for the Baron Dominion card.
 * 
 * ***********************************************/

#define NOISY_TEST 0

#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
//#include "dominion.c"
#include <math.h>
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

// count number cards in array
int countCards(int array[], int size, int card)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == card) sum++;

    return sum;
}

void checkBaron(struct gameState *state, int choice1, int currentPlayer)
{
    int oEstateSupply = state->supplyCount[estate];
    int oEstateHand = countCards(state->hand[currentPlayer], state->handCount[currentPlayer], estate);
    int oEstateDeck = countCards(state->deck[currentPlayer], state->deckCount[currentPlayer], estate);
    int oEstateDiscard = countCards(state->discard[currentPlayer], state->discardCount[currentPlayer], estate);

    printf("Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d\n", oEstateSupply, oEstateHand, oEstateDeck, oEstateDiscard);

    // check return value of playBaron
    if(0 == asserttrue(0 == playBaron(state, choice1, currentPlayer)))
    {
        printf("return value not 0\n");
    }

    // if user chose to get gold for estate card
    if(choice1 > 0 )
    {
        // if user has an estate card to trade
        if(oEstateHand > 0)
        {
            // check if estate removed from hand
            int currentEstateHand = countCards(state->hand[currentPlayer], state->handCount[currentPlayer], estate);
            if(0 == asserttrue(oEstateHand == currentEstateHand + 1))
            {
                printf("failed to remove estate card from hand\n");
            }
        }
    }


}



// add a Smithy card to hand
void addBaron(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = smithy;
    state->handCount[player]++;
}

// random tester for Smithy Dominion card
void randTestBaron()
{
    // init game data
    struct gameState *state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  //  initializeGame(2, k, 1, state);

    int p, choice;
    
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
        choice = floor(Random() * 2);
        state->numPlayers = p + floor(Random() * 2);
        state->deckCount[p] = floor(Random() * MAX_DECK);
        state->discardCount[p] = floor(Random() * MAX_DECK);
        state->handCount[p] = floor(Random() * MAX_HAND);
        state->playedCardCount = floor(Random() * MAX_HAND);

        // populate estate cards
        int estateSupply = floor(Random() * 8);
        state->supplyCount[estate] = estateSupply;
        
        estateSupply = 12 - estateSupply;
        estateSupply = floor(Random() * estateSupply);
        for(int i = 0; i < estateSupply; i++)
            state->deck[p][(int)floor(Random() * state->deckCount[p])] = estate;


        estateSupply = floor(Random() * 12);
        for(int i = 0; i < estateSupply; i++)
            state->hand[p][(int)floor(Random() * state->handCount[p])] = estate;




        addBaron(p, state);
        checkBaron(state, choice, p);

        free(state);
    }

}

// test harness for baron
int main()
{
    SelectStream(2);
    PutSeed(3);

    printf("\n\n Testing Baron . . .\n\n");

    randTestBaron();
    return 0;
}