/**************************************************
 * 
 * Assignment 4: randomtestadventurer
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  Random tester for the Adventurer Dominion card.
 * 
 * ***********************************************/

#define NOISY_TEST 0
#define TEST_TEST 1

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
    int oHandCount = state->handCount[currentPlayer];
    int oDeckCount = state->deckCount[currentPlayer];
    int oDiscardCount = state->discardCount[currentPlayer];
    
    int oDeckTreasureCards = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]);
    int oDiscardTreasureCards = countTreasureCards(state->discard[currentPlayer], state->discardCount[currentPlayer]);
    int oHandTreasureCards = countTreasureCards(state->hand[currentPlayer], state->handCount[currentPlayer]);

    int availableTreasureCards = oDeckTreasureCards + oDiscardTreasureCards;
printf("check: oDeckTs: %d, oDiscardTs: %d \n", oDeckTreasureCards, oDiscardTreasureCards);

    // check that playAdventurer returned 0 (success)    
    if(0 == asserttrue(0 == playAdventurer(currentPlayer, state)))//, cardDrawn, drawnTreasure)))
    {
        printf("playAdventurer returned failure" );
    }

    // check that handCount increased by appropriate number of available treasure cards
    int increase = 2;
    if(availableTreasureCards < 2) increase = availableTreasureCards;


if(!TEST_TEST){  
    if(0 == asserttrue(state->handCount[currentPlayer] == oHandCount + increase))
    {
        printf("failure to increase in handCount does not match available treasure cards: handCount: %d -- oHandCount: %d -- availableTreasureCards: %d\n", state->handCount[currentPlayer], oHandCount, availableTreasureCards);
        printf("increase: %d\n", increase);
    }

    //check that the hand now has appropriate increase in treasure cards
    int handTreasureCards = countTreasureCards(state->hand[currentPlayer], state->handCount[currentPlayer]);
    if(0 == asserttrue(handTreasureCards == oHandTreasureCards + increase))
    {
        printf("failure to increase treasure cards in hand: handTreasureCards: %d, oHandTreasureCards: %d, increase: %d\n", handTreasureCards, oHandTreasureCards, increase);
    }


    // check that the deck & discard have fewer cards
    int deckPlusDiscardCount = state->deckCount[currentPlayer] + state->discardCount[currentPlayer];
    int oDeckPlusDiscardCount = oDeckCount + oDiscardCount;

    if(0 == asserttrue(oDeckPlusDiscardCount == deckPlusDiscardCount + increase))
    {
        printf("failure to move cards from deck & discard to hand\n");
    }


    // check that deck & discard have fewer treasure cards
    int deckPlustDiscardTreasure = countTreasureCards(state->deck[currentPlayer], state->deckCount[currentPlayer]);
      deckPlustDiscardTreasure += countTreasureCards(state->discard[currentPlayer], state->discardCount[currentPlayer]);
    int oDeckPlusDiscardTreasure = oDeckTreasureCards + oDiscardTreasureCards;

    if(0 == asserttrue(deckPlustDiscardTreasure == oDeckPlusDiscardTreasure - increase))
    {
        printf("failure to decrease treasure cards from deck and discard\n");
    }
  }////////
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