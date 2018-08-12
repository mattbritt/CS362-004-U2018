// Paul Robinson
// robinsop
// CS362-400 Summer 2018
// Assignment 4
// randomtestadventurer


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int myAssert(int expected, int actual){
  if (expected == actual){
    printf("TEST PASSED\n");
    return 0;
  }
  else {
    printf("Expected %d, actual %d, TEST FAILED!!!!!!\n", expected, actual);
    return 1;
  }
}

// fill adventurer hand with different numbers of cards

// see if works


int main(){

  srand(time(0));

  int seed = 1000;
  int numPlayer = 2;
  int r;
  int i;
  int j;
  int x;
  int treasureCount = 0;
  int k[10] = {adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall};
  struct gameState G;
  int bonus;


  for (i = 0; i < 500; i++){
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    treasureCount = 0;


    G.handCount[0] = rand() % 7 + 1;
    int preserveHandCount = G.handCount[0];
    G.deckCount[0] = rand() % 8;
    G.discardCount[0] = rand() % 8;

    // make sure an adventurer is in hand
    G.hand[0][0] = adventurer;

    for (j = 1; j < G.handCount[0]; j++){
      G.hand[0][j] = k[rand() % 10];
    }


    for (j = 0; j < G.deckCount[0]; j++){
      x = rand() % 13;
      if (x == 10){
        G.deck[0][j] = copper;
        treasureCount++;
      }
      else if (x == 11){
        G.deck[0][j] = silver;
        treasureCount++;
      }
      else if (x == 12){
        G.deck[0][j] = gold;
        treasureCount++;
      }
      else {
        G.deck[0][j] = k[x];
      }
    }

    int preserveDeckCount = G.deckCount[0];
    for (j = 0; j < G.discardCount[0]; j++){
      G.discard[0][j] = k[rand() % 10];
    }
    int preserveDiscardCount = G.discardCount[0];

    // final hand count depends on if treasures are available
    x = 0;
    if (treasureCount > 2){
      x = 2;
    }
    else {
      x = treasureCount;
    }


    cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
    printf("treasure count is %d\n", treasureCount);
    printf("were: hand %d deck %d discard %d\n", preserveHandCount, preserveDeckCount, preserveDiscardCount);
    printf("are: hand %d deck %d discard %d\n", G.handCount[0], G.deckCount[0], G.discardCount[0]);
    myAssert(preserveHandCount + x - 1, G.handCount[0]);
  }





  return 0;
}