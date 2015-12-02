#include "tlpi_hdr.h"

static int idata = 111;
int
main(int argc, char *argv[])
{
  int istack = 222;
  pid_t childPid;

  if ((childPid = fork()) == -1)
    errExit("fork");
  else if (childPid == 0) {
    idata *= 3;
    istack *= 3;
  } else
    sleep(3);

  printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(), (childPid == 0) ? "(child)" : "(parent)", idata, istack);
  exit(EXIT_SUCCESS);
}
