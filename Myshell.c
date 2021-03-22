#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#define SIZE 256
#define NUM 16
int main()
{
  const char *cmd_line = "[Myshell@VM-0-2-centos Myshell]$ ";
  char cmd[SIZE];
  while(1)
  {
    printf("%s",cmd_line);
    cmd[0]= '\0';
    fgets(cmd,SIZE,stdin);   //会把最后输入完毕的换行符也当作数据录入，所以最后一个置“\0”
    cmd[strlen(cmd)-1]='\0';
    char *args[NUM];
    args[0]=strtok(cmd," ");
    int i=0;
    while(args[i]!=NULL)
    {
      args[++i]=strtok(NULL," ");
    }
    pid_t id=fork();
    if(id<0)
    {
      //child
      printf("fork error\n");
      continue;
    }
    else if(0==id)
    {
      execvp(args[0],args);
      exit(1);
    }
    int status=0;
    pid_t ret =waitpid(id,&status,0);
    if(ret>0)
    {
      printf("status code:%d\n",(status>>8)&0xff);
    }
  }
  return 0;
}
