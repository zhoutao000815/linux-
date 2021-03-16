#include<stdio.h>
#include<unistd.h>
int main ()
{
  printf("1s\n");
  printf("2s\n");
  printf("3s\n");
  printf("swap begin...\n");
  execl("/bin/ls","ls","-al",NULL);
  //进程替换后，后面的代码不再执行！
  char *const argv[] = {"ps","-ef",NULL};
  char *const envp[] = {"PATH=/bin:/usr/bin","TERM=console", NULL};
  execl("/bin/ps", "ps", "-ef", NULL);
  // 带p的，可以使用环境变量PATH，无需写全路径
  // execlp("ps", "ps", "-ef", NULL);
  // // 带e的，需要自己组装环境变量
  // execle("ps", "ps", "-ef", NULL, envp);
  // execv("/bin/ps", argv);
  // // 带p的，可以使用环境变量PATH，无需写全路径
  // execvp("ps", argv);
  // // 带e的，需要自己组装环境变量
  // execve("/bin/ps", argv, envp);
  printf("swap end...\n");
  return 0;
}
