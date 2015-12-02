#include "tlpi_hdr.h"

#define BUF_SIZE 1024
#define LINE_SIZE 100

char inBuffer[BUF_SIZE];
char outBuffer[BUF_SIZE];

int
main(int argc, char *argv[])
{
  char line[LINE_SIZE];
  if (setvbuf(stdin, inBuffer, _IOFBF, BUF_SIZE) != 0)
    errExit("setvbuf");
  if (setvbuf(stdout, outBuffer, _IOFBF, BUF_SIZE) != 0)
    errExit("setvbuf");
  while (fscanf(stdin, "%s", line) != EOF)
    fprintf(stdout, "%s\n", line);

  exit(EXIT_SUCCESS);
}
