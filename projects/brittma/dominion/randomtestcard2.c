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
    int oCoins = state->coins;
    int oNumBuys = state->numBuys;
    int oNumActions = state->numActions;

    printf("Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", oEstateSupply, oEstateHand, oEstateDeck, oEstateDiscard, choice1);

    // check return value of playBaron
    if(0 == asserttrue(0 == playBaron(state, choice1, currentPlayer)))
    {
        printf("return value not 0\n");
    }

    int currentEstateDiscard = countCards(state->discard[currentPlayer], state->discardCount[currentPlayer], estate);
    int currentEstateHand = countCards(state->hand[currentPlayer], state->handCount[currentPlayer], estate);
    int currentEstateDeck = countCards(state->deck[currentPlayer], state->deckCount[currentPlayer], estate);    


    if(0 == asserttrue(oNumBuys == state->numBuys))
    {
        printf("numBuys has changed\n");
    }


    // if user chose to get gold for estate card
    if(choice1 > 0 )
    {
        // if user has an estate card to trade
        if(oEstateHand > 0)
        {
            // check if estate removed from hand
            if(0 == asserttrue(oEstateHand == currentEstateHand + 1))
            {
                printf("failed to remove estate card from hand\n");
            }
            
            // check if coins +4
            if(0 == asserttrue(oCoins == state->coins - 4))
            {
                printf("failed to add 4 coins\n");
            }

            // check if discard num estates +1
            if(0 == asserttrue(oEstateDiscard == currentEstateDiscard - 1))
            {
                printf("failed to add estate to discard\n");
            }
        }
        // else a user does not have an estate to trade
        else
        {
            // check if estate removed from hand (should not be)
            if(0 == asserttrue(oEstateHand == currentEstateHand))
            {
                printf("estate cards in hand changed without trading estate card\n");
            }
            
            // check if coins changed (should not have)
            if(0 == asserttrue(oCoins == state->coins))
            {
                printf("coins changed without trading estate card\n");
            }

            // check if discard num estates changed
            if(oEstateSupply > 0)
            {
                // check if supply decremented
                if(0 == asserttrue(oEstateSupply == state->supplyCount[estate] + 1))
                {
                    printf("estate supply failed to decrement 1\n");
                    printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
                }

                // check if player gained the estate card
                if(0 == asserttrue(oEstateDiscard == currentEstateDiscard - 1))
                {
                    printf("discard failed to increment\n");
                    printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
 
                }

            }
            //else no estate cards to gain, nothing should happen 
            else{
                // check that supply is unchanged
                if(0 == asserttrue(oEstateSupply == state->supplyCount[estate]))
                {
                    printf("number of estate cards in supply changed without trading estate card\n");
                    printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
                }
                // check that coins are unchanged
                if(0 == asserttrue(oCoins == state->coins))
                {
                    printf("number of coins changed without trading estate card\n");
                    printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
                }

                // check that discard is unchanged
                if(0 == asserttrue(oEstateDiscard == currentEstateDiscard))
                {
                    printf("number of estate cards in discard changed without trading estate card\n");
                    printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
                }
            }
        }
    }

    // else choice is false
    else
    {
        // check that coins are unchanged
        if(0 == asserttrue(oCoins == state->coins))
        {
            printf("number of coins changed without trading estate card\n");
            printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
        }

        // check that hand is unchanged
        if(0 == asserttrue(oEstateHand == currentEstateHand))
        {
            printf("number of estate cards in hand changed without trading estate card\n");
            printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
        }    

        // if estate card available
        if(oEstateSupply > 0)
        {
            // check that supply is decremented
            if(0 == asserttrue(oEstateSupply == state->supplyCount[estate] + 1))
            {
                printf("number of estate cards in supply failed to decrement\n");
                printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
            } 

            // check that estate card in discard            
            if(0 == asserttrue(oEstateDiscard == currentEstateDiscard - 1))
            {
                printf("number of estate cards in discard failed to increment\n");
                printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
            } 
        }   

        //else estate card not available
        else
        {
            // check that supply is unchanged
            if(0 == asserttrue(oEstateSupply == state->supplyCount[estate]))
            {
                printf("number of estate cards in supply changed with no avialable estate cards\n");
                printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
            } 

            // check that discard is unchanged
            if(0 == asserttrue(oEstateDiscard == currentEstateDiscard))
            {
                printf("number of estate cards in discard changed with no available estate cards\n");
                printf(" --- Estate Supply: %d, Hand: %d, Deck: %d, Discard: %d, choice: %d\n", state->supplyCount[estate], currentEstateHand, currentEstateDeck, currentEstateDiscard, choice1);
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

        // add Baron card to end of hand
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