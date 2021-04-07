#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
  int pipefd[2];
  char buff[64];
  int piperet=pipe(pipefd); 
  if(piperet==-1)
  {
    perror("pipe creat error\n");
  }

  pid_t id=fork();
  if(id>0)
  {
    //father
    //父进程写入管道
    close(pipefd[0]);
    const char * msg="i am father!";
    write(pipefd[1],msg,strlen(msg));
    close(pipefd[1]);

  }
  else if(0==id)
  {
    //child
    //子进程从管道读
    close(pipefd[1]);
    int readret=read(pipefd[0],buff,sizeof(buff));
    if(readret==-1)
    {
      perror("read error!\n");
    }
    buff[readret]=0;
    write(1,buff,strlen(buff));
    close(pipefd[0]);
    _exit(0);
  }
  else 
  {
    perror("fork error\n");
    _exit(2);
  }
  return 0;
}
