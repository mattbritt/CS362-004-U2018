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
    int oNumTreasureCardsDeck = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]) + countTreasureCards(state->discard[currentPlayer], state->discardCount[currentPlayer]);
    int oNumDiscardCards = state->discardCount[currentPlayer];
    int oNumDeckCards = state->deckCount[currentPlayer];
    int oNumHandCards = state->handCount[currentPlayer];
    int totalTreasure = fullDeckCount(currentPlayer, copper, state) + fullDeckCount(currentPlayer, silver, state) + fullDeckCount(currentPlayer, gold, state);
printf("******************** oNUmTreasureCardsHand: %d -- oNumTreasureCardsDeck: %d -- totalTreasure: %d\n", oNumTreasureCardsHand, oNumTreasureCardsDeck, totalTreasure);
    // check that playAdventurer returned 0 (success)    
    if(0 == asserttrue(0 == playAdventurer(currentPlayer, state)))//, cardDrawn, drawnTreasure)))
    {
        printf("playAdventurer returned failure" );
    }
//printf("playAdventurer returned\n");
    int NumTreasureCardsHand = countTreasureCards(state->hand[currentPlayer], state->handCount[currentPlayer]);
    int NumTreasureCardsDeck = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]);
    int availableTreasureCards = totalTreasure - oNumHandCards;

    // check that number of cards removed from deck == number added to hand
    // note: differences may be negative due to the shuffle
    if(0 == asserttrue( (oNumDeckCards - state->deckCount[currentPlayer]) == (state->discardCount[currentPlayer] - oNumDiscardCards)))
    {
        printf("failed to add cards removed from deck to discard: removed from deck: %d -- added to discard: %d\n", (oNumDeckCards - state->deckCount[currentPlayer]),  (state->discardCount[currentPlayer] - oNumDiscardCards));
    }

    // check that # treasure cards in hand is valid based on available treasure cards
    if(0 == asserttrue(NumTreasureCardsHand == oNumTreasureCardsHand - availableTreasureCards))
    {
        printf("treasure cards in hand changed but no treasure cards were available: oNumTreasureCards: %d -- NumTreasureCards: %d\n", NumTreasureCardsHand, oNumTreasureCardsHand - availableTreasureCards);
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

int randomTreasureCard()
{
    switch((int)floor(Random() * 3))
    {
        case 0: return copper;
        case 1: return silver;
    }
    return gold;
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

    // randomly add treasure cards to hand, deck and discard
        int randNumTreasureCards = floor(Random() * 5);
        for(int i = 0; i < randNumTreasureCards; i++)
            state->hand[p][(int)floor(Random()* state->handCount[p])] = randomTreasureCard(); 

        randNumTreasureCards = floor(Random() * 5);
        for(int i = 0; i < randNumTreasureCards; i++)
            state->deck[p][(int)floor(Random()* state->deckCount[p])] = randomTreasureCard(); 

        randNumTreasureCards = floor(Random() * 5);
        for(int i = 0; i < randNumTreasureCards; i++)
            state->discard[p][(int)floor(Random()* state->discardCount[p])] = randomTreasureCard(); 



        addAdventurer(p, state);
        checkAdventurer(p, state);

        free(state);
    }
}

// test harness for adventurer
int main()
{
    SelectStream(2);
    PutSeed(-1);//3);

    printf("\n\n Testing Adventurer\n\n");

    randTestAdventuer();
    return 0;
}