#include <stdio.h>
#include <syscall.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{

  if (argc != 5) 
    {
      printf ("usage: ./additional [num1] [num2] [num3] [num4]\n");
      return EXIT_FAILURE;
    }

  int n1, n2, n3, n4;
  n1 = atoi(argv[1]);
  n2 = atoi(argv[2]);
  n3 = atoi(argv[3]);
  n4 = atoi(argv[4]);

  if (!fibonacci(n1)) 
    {
      printf ("%s: fibonacci failed\n", argv[1]);
      return EXIT_FAILURE;
    }

  if (!max_of_four_int(n1, n2, n3, n4)) 
    {
      printf ("%s %s %s %s: max_of_four_int failed\n", argv[1], argv[2], argv[3], argv[4]);
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
