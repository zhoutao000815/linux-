#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
  //手动重定向
  //close(1);
  
 // int fp=open("zhoutao.txt",O_CREAT | O_RDWR | O_APPEND,0644);
 // printf("fd:%d \n",fp);
 // //fflush(stdout);
 // const char* msg="人生难免会有遗憾!\n";
 // write(fp,msg,strlen(msg));
 // close(fp);
 // =================================================================
 //
 // 系统调用接口重定向
    
 return 0;
}
