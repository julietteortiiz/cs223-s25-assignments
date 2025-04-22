#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* signal handler for SIGINT */
void sigint_handler(int sig) {
    printf("Help! I've been shot! %d\n.", sig);
    fflush(stdout);
    exit(0);
}


int main()
{

  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        printf("Error call to signal, SIGINT\n");
        exit(1);
    }

  while(1){
    printf("loop\n");
  };
  return 0;


}
