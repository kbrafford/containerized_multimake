#include <stdio.h>
#include "mylib.h"

int main(int argc, char *argv[])
{
  int a = 1;
  int b = 2;

  printf("Hello World!  My lib function result is: %d\n", my_lib_function(a,b));
}