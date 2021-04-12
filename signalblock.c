#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main()
{
  sigset_t sig;
  sigemptyset(&sig);
  sigaddset(&sig,/*SIGINT|*/ SIGRTMIN+6);

  sigprocmask(SIG_SETMASK,&sig,NULL);
  while(1)
  {
    sleep(1);
    printf("runing!\n");
  }
  return 0;
}
