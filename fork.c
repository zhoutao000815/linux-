#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
 /* printf("fork之前：\n");
  int ret=fork();
  sleep(1);
  printf("fork之后：pid：%d，ppid：%d ,ret: %d\n",getpid(),getppid(),ret);
  sleep(1);
  printf("即将返回\n");*/
  printf("bash:%d\n",getppid());  
  int ret = fork();
  if(ret < 0){
     perror("fork");
      return 1;
  }
   else if(ret == 0){ //child
    printf("I am child : %d!, return值: %d\n", getpid(), ret);
    }else{ //father
     printf("I am father : %d!, return值: %d\n", getpid(), ret);
     }
    sleep(1);

  return 0;
}
