#include <signal.h>
#include "tlpi_hdr.h"

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

static void
printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
  int sig, cnt;
  cnt = 0;
  for (sig = 1; sig < NSIG; ++sig) {
    if (sigismember(sigset, sig)) {
      ++cnt;
      fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
    }
  }
  if (cnt == 0)
    fprintf(of, "%s<empty signal set>\n", prefix);
}

static void
handler(int sig)
{
  if (sig == SIGINT)
    gotSigint = 1;
  else
    sigCnt[sig]++;
}

int
main(int argc, char *argv[])
{
  int n, numSecs;
  sigset_t pendingMask, blockingMask, emptyMask;

  printf("%s: PID is %ld\n", argv[0], (long) getpid());

  for (n = 1; n < NSIG; ++n)
    signal(n, handler);

  if (argc > 1) {
    numSecs = getInt(argv[1], GN_GT_0, NULL);

    sigfillset(&blockingMask);
    // block all signals
    if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
      errExit("sigprocmask");

    printf("%s: sleeping for %d seconds\n", argv[0], numSecs);
    sleep(numSecs);

    // get pending mask
    if (sigpending(&pendingMask) == -1)
      errExit("sigpending");

    // print pending mask
    printf("%s: pending signals are: \n", argv[0]);
    printSigset(stdout, "\t\t", &pendingMask);

    sigemptyset(&emptyMask);
    if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
      errExit("sigprocmask");
  }

  while (!gotSigint)
    continue;

  for (n = 1; n < NSIG; ++n)
    if (sigCnt[n] != 0)
      printf("%s: signal %d caught %d time%s\n", argv[0], n, sigCnt[n], (sigCnt[n] == 1) ? "" : "s");

  exit(EXIT_SUCCESS);
}
