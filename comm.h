#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define PATHNAME "zhoutao"
#define PROJ_ID 0x000815

static int commshm(int size,int flag)
{
  key_t key=ftok(PATHNAME,PROJ_ID);
  if(key==-1)
  {
    perror("ftok error");
    _exit(-1);
  }
  int shmid=shmget(key,size,flag);
  if(shmid<0)
  {
    perror("shmget error");
    _exit(-2);
  }
  return shmid;
}

int destroyShm(int shmid)
{
  if(shmctl(shmid, IPC_RMID, NULL) < 0){
    perror("shmctl");
    return -1;
  }
  return 0;
}

int creatShm(int size)
{
  return commshm(size, IPC_CREAT|IPC_EXCL|0666);
}
  
int getShm(int size)
{
  return commshm(size, IPC_CREAT);

}
