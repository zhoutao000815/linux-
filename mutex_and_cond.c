#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

char str[20]="i am pthreadA!";
pthread_mutex_t lock;
pthread_cond_t condA;
pthread_cond_t condB;

void* pthA(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(str[12]=='B')
    {
      pthread_cond_wait(&condA,&lock); 
    }
    printf(" %s  :%lu\n",str,pthread_self());
    sleep(1);
    str[12]='B';
    pthread_cond_signal(&condB);  
    pthread_mutex_unlock(&lock);
  }
}

void* pthB(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(str[12]=='A')
    {
      pthread_cond_wait(&condB,&lock);
    }
    printf(" %s  :%lu\n",str,pthread_self());
    sleep(5);
    str[12]='A';
    pthread_cond_signal(&condA);  
    pthread_mutex_unlock(&lock);
  }
}

int main()
{
  pthread_t A,B;

  pthread_mutex_init(&lock,NULL); 
  pthread_cond_init(&condA,NULL);
  pthread_cond_init(&condB,NULL);

  pthread_create(&A,NULL,pthA,NULL);
  pthread_create(&B,NULL,pthB,NULL);

  pthread_join(A,NULL);
  pthread_join(B,NULL);

  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&condA);
  pthread_cond_destroy(&condB);
  return 0;
}
