#include "tlpi_hdr.h"

int
main(void) {
  pid_t childPid;
  printf("main: %ld\n", (long) getpid());
  if ((childPid = fork()) == -1)
    errExit("fork");
  printf("%ld\n", (long) getpid());
  if ((childPid = fork()) == -1)
    errExit("fork");
  printf("%ld\n", (long) getpid());
  if ((childPid = fork()) == -1)
    errExit("fork");
  printf("%ld\n", (long) getpid());
  exit(EXIT_SUCCESS);
}
