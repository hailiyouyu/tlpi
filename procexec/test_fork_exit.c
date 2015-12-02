#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  int istack = 222;

  switch (fork()) {
  case -1:
    errExit("fork");
  case 0:
    printf("Executing Child\n");
    istack *= 3;
    printf("Child's istack=%d\n", istack);
    exit(EXIT_SUCCESS);
  default:
    printf("Executing Parent\n");
    printf("Parent's istack=%d\n", istack);
    exit(EXIT_SUCCESS);
  }
}
