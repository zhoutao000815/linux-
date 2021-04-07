#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main ()
{
  int fiforet=mkfifo("myfifo",0644);
  if(fiforet<0)
  {
    perror("mkfifo error!");
    _exit(2);
  }
  int sfd=open("myfifo",O_RDONLY);
  if(sfd<0)
  {
    perror("open error!");
    _exit(3);
  }
  char buff[1024];
  while(1)
  {
    int readret=read(sfd,buff,sizeof(buff)-1);
    buff[readret]=0;
    if(readret>0)
    {
      printf("cliet say:");
      fflush_unlocked(stdout);
      write(1,buff,strlen(buff));
    }
    else if(readret==0)
    {
      printf("client exit,exit now! \n");
      break;
    }
    else 
    {
      perror("read error!");
    }
  }
  return 0;
}
