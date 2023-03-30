#include "kernel/types.h"
#include "user/user.h"

int main() {
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  char buf[2];
  int pid;

  if (fork() == 0) {
    pid = getpid();
    read(p1[0], buf, 1);
    printf("%d: received ping\n", pid);
    write(p2[1], "w", 1);
  } else {
    pid = getpid();
    write(p1[1], "q", 1);
    read(p2[0], buf, 1);
    printf("%d: received pong\n", pid);
  }



  exit(0);
}
