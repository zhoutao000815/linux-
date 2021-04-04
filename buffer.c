#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
  //dup2（）示例
  //close(1);
  //int fd = open("zhoutao.txt", O_CREAT | O_RDWR,0644);
  //    if (fd < 0)
  //    {
  //       perror("open");
  //       return 1;
  //   }
  //dup2(fd, 1);             //重定向系统调用接可
  //const char* msg="人生难免会有遗憾！\n";
  //write(1,msg,strlen(msg));
  //printf("printf:fd:%d\n",1);
  //fflush(stdout);
  
  //缓冲区验证
  close(1);
  const char *msg0="hello printf\n";
  const char *msg1="hello fwrite\n";
  const char *msg2="hello write\n";
  int fd = open("zhoutao.txt", O_CREAT | O_RDWR,0644);  
  if (fd < 0) {  
  perror("open");  
  return 1;  
  }  

  printf("%s", msg0);
  fwrite(msg1, strlen(msg0), 1, stdout);
  write(1, msg2, strlen(msg2));

  fork();
  return 0;
}
