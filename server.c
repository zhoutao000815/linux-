#include"comm.h"

int main()
{
  int shmid=creatShm(2048);
  void *addr=shmat(shmid,NULL,0); 
  int i=0;
  while(i++<60)
  {
    printf("client : # %s\n",addr);
    sleep(1);
  }
  shmdt(addr);
  printf("delete attach!\n");
  destroyShm(shmid);
  return 0;
}
