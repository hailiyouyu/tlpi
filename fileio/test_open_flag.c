#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  int fd1, fd2, fd3;
  
  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s filename\n", argv[0]);

  fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd1 == -1)
    errExit("open");

  fd2 = dup(fd1);
  if (fd2 == -1)
    errExit("dup");

  fd3 = open(argv[1], O_RDWR);
  if (fd3 == -1)
    errExit("open");

  write(fd1, "Hello,", 6);

  write(fd2, "world", 6);

  lseek(fd2, 0, SEEK_SET);

  write(fd1, "HELLO,", 6);

  write(fd3, "Gidday", 6);

  exit(EXIT_SUCCESS);
}
