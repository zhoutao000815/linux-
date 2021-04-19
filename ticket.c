#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int tickets=10000;                   //临界资源
pthread_mutex_t lock;                //使线程看到同一把锁

void* rout(void* arg)
{
  while(1)
  {
      usleep(1000);                       //由于进程创建和等待互斥锁的时间差异，有可能会出现一个线程抢走了所有的票，所以要模拟时间差。
    pthread_mutex_lock(&lock);            //上锁
    if(tickets>0)
    {
      usleep(1000);
      printf("%s_id:%lu     ",(char*)arg,pthread_self());
      printf("get tickets success:%d!\n",tickets);
      tickets--;
      pthread_mutex_unlock(&lock);         //解锁
    }
    else
    {
      printf("%s_id:%lu     ",(char*)arg,pthread_self());
      printf("have no tickets!\n");
      pthread_mutex_unlock(&lock);          //推出前解锁:锁要上在正确的位置，临界区越精确越好。
      break;
    }
  }
  //pthread_exit(retval);                  //三种退出方式，
  //return 0;
  pthread_cancel(pthread_self());
  return NULL;
}


int main()
{
  pthread_mutex_init(&lock,NULL);
  pthread_t t[4];
  int i=4;
  char s[]="pthread";
  for(i=0;i<4;i++)
  {
    pthread_create(t+i,NULL,rout,s);
  }

  pthread_join(t[0],NULL);
  pthread_join(t[1],NULL);
  pthread_join(t[2],NULL);
  pthread_join(t[3],NULL);

  pthread_mutex_destroy(&lock);           //记得将互斥锁释放
  return 0;
}
