/**************************************************
 * 
 * Assignment 4: randomtestadventurer
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  Random tester for the Adventurer Dominion card.
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


// count adventurer cards from given array
int adventurerCount(int array[], int size)
{
    int count = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == smithy) count++;

    return count;
}

// count number of treasure cards in given array
int countTreasureCards(int array[], int size)
{
    int count = 0;
    for(int i = 0; i < size; i++)
        if(array[i] == copper || array[i] == silver || array[i] == gold)
            count++;
    return count;
}

// check if adventurer card performs as expected
void checkAdventurer(int currentPlayer, struct gameState *state)
{
    int oNumTreasureCardsHand = countTreasureCards(state->hand[currentPlayer], state->handCount[currentPlayer]);
    int oNumTreasureCardsDeck = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]);
   // int oNumDiscardCards = state->discardCount[currentPlayer];
    int oNumDeckCards = state->deckCount[currentPlayer];
    int oNumHandCards = state->handCount[currentPlayer];

    // check that playAdventurer returned 0 (success)    
    if(0 == asserttrue(0 == playAdventurer(currentPlayer, state)))//, cardDrawn, drawnTreasure)))
    {
        printf("playAdventurer returned failure" );
    }

    int NumTreasureCardsHand = countTreasureCards(state->hand[currentPlayer], state->handCount[currentPlayer]);
    int NumTreasureCardsDeck = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]);
    
    // check that number of cards removed from deck == number added to hand
    if(0 == asserttrue( (oNumDeckCards - state->deckCount[currentPlayer]) == (state->handCount[currentPlayer] - oNumHandCards)))
    {
        printf("failed to add cards removed from deck to hand: removed from deck: %d -- added to hand: %d\n", (oNumDeckCards - state->deckCount[currentPlayer]),  (state->handCount[currentPlayer] - oNumHandCards));
    }

    // if there were two treasure cards to remove from deck
    if(oNumTreasureCardsDeck >= 2)
    {    // check that two treasure cards were added to hand
        if(0 == asserttrue(NumTreasureCardsHand == oNumTreasureCardsHand + 2))
        {
            printf("failed to add 2 treasure cards to hand: oNumTreasureCardsHand: %d -- NumTreasureCardsHand: %d\n", oNumTreasureCardsHand, NumTreasureCardsHand);
        }
        // check that two treasure cards were removed from deck
        if(0 == asserttrue(NumTreasureCardsDeck == oNumTreasureCardsDeck - 2))
        {
            printf("failed to remove 2 treasure cards from deck: oNumTreasureCards: %d -- NumTreasureCards: %d\n", oNumTreasureCardsDeck, NumTreasureCardsDeck);
        }
    }
    // else there were less than 2 treasure cards in deck
    else
    {

    }

}

// add adventurer to the hand
void addAdventurer(int player, struct gameState* state)
{
    state->hand[player][state->handCount[player]] = adventurer;
    state->handCount[player]++;
}

// set up testing for adventurer card
void randTestAdventuer()
{
    // init game data
    struct gameState *state;
 /*   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
*/
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
        addAdventurer(p, state);
        checkAdventurer(p, state);

        free(state);
    }
}

// test harness for adventurer
int main()
{
    SelectStream(2);
    PutSeed(3);

    printf("\n\n Testing Adventurer\n\n");

    randTestAdventuer();
    return 0;
}