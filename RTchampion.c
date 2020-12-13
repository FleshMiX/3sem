#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int cur_pid;

void signal1(int s) {
  printf("РТ\n");
  sleep(1);
  kill(cur_pid, SIGUSR2);
}

void signal2(int s) {
  printf("Чемпион!!!\n");
  sleep(1);
  kill(cur_pid, SIGUSR1);
}

void run1() {
  signal1(0);
  while(1);
}

int main() {

  signal(SIGUSR1, signal1);
  signal(SIGUSR2, signal2);

  cur_pid = getpid();

  run1();

  return 0;
}
