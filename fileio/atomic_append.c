#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  int outputFd, openFlags, i;
  mode_t filePerms;
  size_t len;
  Boolean hasX = FALSE;
  char buf[1] = {'\0'};
  
  if (argc < 3 || argc > 4 || strcmp(argv[1], "--help") == 0)
    usageErr("%s filename num-bytes [x]\n", argv[0]);


  openFlags = O_WRONLY | O_CREAT | O_APPEND;
  if (argc == 4 && strcmp(argv[3], "x") == 0) {
    openFlags &= ~O_APPEND;
    hasX = TRUE;
  }

  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

  outputFd = open(argv[1], openFlags, filePerms);
  if (outputFd == -1)
    errExit("open");

  len = getLong(argv[2], GN_ANY_BASE, argv[2]);

  if (hasX) {
    for (i = 0; i < len; ++i) {
      if (lseek(outputFd, 0, SEEK_END) == -1)
        errExit("seek");
      if (write(outputFd, buf, 1) != 1)
        errExit("write");
    }
  } else {
    for (i = 0; i < len; ++i)
      if (write(outputFd, buf, 1) != 1)
        errExit("write");
  }

  exit(EXIT_SUCCESS);
}
  
