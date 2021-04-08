#include"comm.h"
#include<string.h>
int main()
{
  int shmid=getShm(2048);
  char * addr=(char *)shmat(shmid,NULL,0);
  int i=0;
  char buff [2048];
  while(i++<60)
  {
    printf("enter please!\n");
    int readret=read(0,buff,sizeof(buff)-1);
    buff[readret]=0;
    if(readret>0)
    {
      memcpy(addr,buff,strlen(buff)+1);
    }
    sleep(1);
    addr[0]=0;
  }
  shmdt(addr);
  printf("exit!\n");
  return 0 ;
}
