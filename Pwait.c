#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
int main ()
{
  int st;
  pid_t id=fork();
  if(0==id)
  {
    //child
    int i=1;
    printf("I am child process  pid:%d  \n",getpid());
    while(i<=5)
    {
      sleep(1);
      printf("%ds\n",i++);
    }
    exit(10);
  }
  else if(id>0)
  {
    //father
    printf("I am father process pid:%d  \n",getpid());
    printf("before waiting....\n");
    int ret=wait(&st);
    printf("end  waiting....\n");
    if(ret>0 && (st&0x7F)==0)
    {
      printf("child exit code:%d\n",(st>>8)&0xFF);
    }
    else if(ret>0)
    {
      printf("sig code:%d\n",st & 0x7F);
    }
  }
  else 
  {
    //error
    printf("error \n");
    exit(0);
  }
  return 0;
}
