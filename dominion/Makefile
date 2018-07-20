CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresult: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	echo "Result for running dominion.c unit tests: " > tests.out

	echo >> tests.out
	echo "unittest1.c (numHandCards):" >> tests.out
	gcc -o unittest1 unittest1.c -g dominion.c rngs.c $(CFLAGS)
	unittest1 >> tests.out
	#gcov -b -f dominion.c >> tests.out
	#lcov --capture --directory ./ --output-file numHandCards.info 

	echo >> tests.out
	echo "unittest2.c (fullDeckCount):" >> tests.out
	gcc -o unittest2 unittest2.c -g dominion.c rngs.c $(CFLAGS)
	unittest2 >> tests.out
	#gcov -b -f dominion.c >> tests.out
	#lcov --capture --directory ./ --output-file fullDeckCount.info  

	echo >> tests.out
	echo "unittest3.c (scoreFor):" >> tests.out
	gcc -o unittest3 unittest3.c -g dominion.c rngs.c $(CFLAGS)
	unittest3 >> tests.out
	#gcov -b -f dominion.c >> tests.out
	#lcov --capture --directory ./ --output-file scoreFor.info  

	echo >> tests.out
	echo "unittest4.c (whoseTurn):" >> tests.out
	gcc -o unittest4 unittest4.c -g dominion.c rngs.c $(CFLAGS)
	unittest4 >> tests.out
	#gcov -b -f dominion.c >> tests.out 
	#lcov --capture --directory ./ --output-file whoseTurn.info 

	#genhtml numHandCards.info --output-directory UT1
	#genhtml fullDeckCount.info --output-directory UT2
	#genhtml scoreFor.info --output-directory UT3
	#genhtml whoseTurn.info --output-directory UT4

	echo >> tests.out
	echo "cardtest1.c (Smithy):" >> tests.out
	gcc -o cardtest1 cardtest1.c -g dominion.c rngs.c $(CFLAGS)
	cardtest1 >> tests.out
	#gcov -b -f dominion.c >> tests.out

	echo >> tests.out
	echo "cardtest2.c (Adventurer):" >> tests.out
	gcc -o cardtest2 cardtest2.c -g dominion.c rngs.c $(CFLAGS)
	cardtest2 >> tests.out
	#gcov -b -f dominion.c >> tests.out

	echo >> tests.out
	echo "cardtest3.c (Baron):" >> tests.out
	gcc -o cardtest3 cardtest3.c -g dominion.c rngs.c $(CFLAGS)
	cardtest3 >> tests.out
	#gcov -b -f dominion.c >> tests.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
