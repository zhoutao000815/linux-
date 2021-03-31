#include<iostream>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
int main()
{
  int fd =open("bite",O_CREAT | O_RDWR,0644);
  if(fd<0)
  {
    cout<<"open error"<<endl;
  } 
  const char* s="i like linux!";
  int len =strlen(s);
  write(fd,s,len);
  lseek(fd,0,SEEK_SET);
  char buf [1024];
  size_t ret=read(fd,buf,len);
  if(ret>0)
  {
    cout<<buf<<endl;
  }
  else 
  {
    cout<<"read error"<<endl;
  }
  close(fd);
  return 0;
}
