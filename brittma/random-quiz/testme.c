/*****************************************
 * 
 *  Name: Random Testing Quiz
 *  Author: Matt Britt
 *  Date: 7/21/2018
 *  Description: inputChar and inputString have been implemented to randomly provide testme() with input until the error is thrown.
 * 
 * ***************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    return 32 + rand() % 94;
}

char *inputString()
{
    static char string[6] = {'\0'};
    char c;

    for(int i = 0; i < 5; i++)
    {
      switch(rand() % 4)
      {
        case 0:
          c = 'r';
          break;
        case 1:
          c = 'e';
          break;
        case 2:
          c = 's';
          break;
        case 3:
          c = 't';
          break;
      }
      string[i] = c;
    }
    return &string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
