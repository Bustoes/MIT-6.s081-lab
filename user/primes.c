#include "kernel/types.h"
#include "user/user.h"

#define MAXNUM 35
#include "kernel/types.h"
#include "user/user.h"

#define MAXNUM 35
#define SIZE sizeof(int)
#define R 0
#define W 1
void a(int pi[]) {
  char n, p;
  int pi_next[2];
  int status;
  pipe(pi_next);
  read(pi[R], &p, SIZE);
  if (p != 0) {
    printf("prime %d\n", p);

    while (read(pi[R], &n, SIZE) == SIZE) {
      if (n % p != 0) {
        write(pi_next[W], &n, SIZE);
        }
      if (n == 0) {
        write(pi_next[W], &n, SIZE);
        close(pi[R]);
      }
    }
    close(pi[R]);
    close(pi[W]);
    if (fork() == 0) {
      a(pi_next);
    } else {
      wait(&status);
      exit(0);
    }
  }
}




int main() {
  int pi[2], zero = 0;
  pipe(pi);
  for (int i = 2; i <= MAXNUM; i++) {
        write(pi[W], &i, SIZE);
  }
  write(pi[W], &zero, SIZE);

  a(pi);




  exit(0);
}
