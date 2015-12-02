#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 10000

int
main(int argc, char *argv[])
{
  int fileDes, dupDes;
  off_t fileOffset, dupOffset;
  char buffer[BUF_SIZE];

  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s filename\n", argv[0]);

  fileDes = open(argv[1], O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
  if (fileDes == -1)
    errExit("open");

  dupDes = dup(fileDes);
  if (dupDes == -1)
    errExit("dup");

  fileOffset = lseek(fileDes, 0, SEEK_CUR);
  if (fileOffset == -1)
    errExit("lseek");

  dupOffset = lseek(dupDes, 0, SEEK_CUR);
  if (dupOffset == -1)
    errExit("lseek");

  if (fileOffset == dupOffset)
    printf("offset is same\n");

  if (write(fileDes, buffer, BUF_SIZE) < 0)
    errExit("write");

  fileOffset = lseek(fileDes, 0, SEEK_CUR);
  dupOffset = lseek(dupDes, 0, SEEK_CUR);

  if (fileOffset == dupOffset)
    printf("after write, offset is same\n");

  if (fcntl(fileDes, F_GETFL) == fcntl(dupDes, F_GETFL))
    printf("open file status flag is same\n");

  exit(EXIT_SUCCESS);
}
