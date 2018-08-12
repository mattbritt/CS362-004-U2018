/**************************************************
 * 
 * Name: asserttrue.h
 * Author: Matt Britt
 * Date: August 1st, 2018
 * Description:  asserttrue is a helper function that tests a condition
 *                 without halting execution.
 * 
 * ***********************************************/

#include <stdio.h>

// asserttrue will output test results
int asserttrue(int test)
{
  if(test)
  {
    if(NOISY_TEST) printf("-- TEST PASSED\n");
    return 1;
  }
  else
  {
    printf("-- *** TEST FAILED ***\n");
    return 0;
  }
}