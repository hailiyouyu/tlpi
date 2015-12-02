#include <sys/wait.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  int numChild, j;
  pid_t childPid;

  if (argc > 1 && strcmp(argv[1], "--help") == 0)
    usageErr("%s [num-children]\n", argv[0]);

  numChild = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-children") : 1;

  setbuf(stdout, NULL);

  for (j = 0; j < numChild; ++j) {
    switch (childPid = fork()) {
    case -1:
      errExit("fork");
    case 0:
      printf("%d child\n", j);
      _exit(EXIT_SUCCESS);
    default:
      printf("%d parent\n", j);
      wait(NULL);
      break;      // break switch
    }
  }
  exit(EXIT_SUCCESS);
}
