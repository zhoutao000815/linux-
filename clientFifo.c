#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
  int cfd=open("myfifo",O_WRONLY);
  if(cfd<0)
  {
    perror("open error!");
  }
  char buff [1024];
  int readret=read(0,buff,1024);
  buff[readret]=0;
  if(readret>0)
  {
    write(cfd,buff,strlen(buff));
  }
  else if(readret==0)
  {
    printf("no input!\n");
  }
  else 
  {
    perror("read error!");
  }
  return 0;
}
