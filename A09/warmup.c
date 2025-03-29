/*
NAME: JULIETTE ORTIZ
DATE: MARCH 29, 2025
DESCRIPTION: PROGRAM CREATES SEVERAL PROCESSES AND PRINTS THEM OUT IN SPECIFIC 
ORDER BY UTILIZING EXIT, WAITPID, AND SIGSTOP + SIGCONT FUNCTIONS

*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
  pid_t pidB0, pidB1, pidC0, pidC1, pidBYEB1, pidBYEC0, pidBYEC1;
  int status;

  printf("[%d] A\n", getpid()); // A0

  pidB0 = fork();
  if (pidB0 == 0)
  { // START B0 BRANCH
    printf("[%d] B0\n", getpid());

    kill(getpid(), SIGSTOP); // PAUSE B1 AND GO TO B0

    pidC0 = fork();
    if (pidC0 == 0) //START C0 BRANCH
    {
      printf("[%d] C0\n", getpid());

      pidBYEC0 = fork();
      if (pidBYEC0 == 0)
      {
        printf("[%d] BYE\n", getpid());
        exit(0);
      }
      wait(NULL); //WAIT FOR BYE TO FINISH
      exit(0); //SIGNAL THAT PROCESS HAS EXITED
    } //FINISH C0

    else
    {

      waitpid(pidC0, &status, 0); //WAIT FOR C0 TO FINISH

      pidC1 = fork(); 
      if (pidC1 == 0) //C1 BRANCH
      {
        printf("[%d] C1\n", getpid());

        pidBYEC1 = fork();
        if (pidBYEC1 == 0)
        {
          printf("[%d] BYE\n", getpid());
          exit(0);
        }
      }
    }
    exit(0);
  } // B0 ends

  else
  { 
    pidB1 = fork();
    if (pidB1 == 0) //B1 BRANCH STARTS
    { // B1 branch

      printf("[%d] B1\n", getpid());

      pidBYEB1 = fork();
      if (pidBYEB1 == 0)
      {
        printf("[%d] Bye\n", getpid());
        exit(0);
      }
      wait(NULL); //WAIT FOR BYE TO FINISH
      kill(pidB0, SIGCONT); //GO BACK TO B0
    } // B1 ends
    exit(0);
  }

  return 0;
}
