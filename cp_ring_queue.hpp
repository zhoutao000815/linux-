#pragma once
#include<iostream>
#include<pthread.h>
#include<vector>
#include<math.h>
#include<semaphore.h>
#include<unistd.h>

struct mask
{
  private:
    int x;
  public:
    mask(int _x=0)
    {
      x=_x;
    }

    int squre()
    {
      int rel=pow(x,2);
      std::cout<<"pthread_id:"<<pthread_self()<<"   ";
      std::cout<<x<<"的平方为: "<<rel<<std::endl;
      return rel;
    }
};

class RingQueue
{
  private:
    std::vector<mask> ring_queue; 
    int cap;
    sem_t data_sem;
    sem_t space_sem;
    int data_step;
    int space_step;

  public:
    RingQueue()
    {}

    void Init(unsigned int _cap=8)
    {
      cap=_cap;
      ring_queue.resize(cap);
      sem_init(&data_sem,0,0);
      sem_init(&space_sem,0,cap);
      data_step =0;
      space_step =0;
    }

    ~RingQueue()
    {
      sem_destroy(&data_sem);
      sem_destroy(&space_sem);
      cap=0;
    }

    void PushData(const mask& in)
    {
      sem_wait(&space_sem);       //P操作
      ring_queue[data_step]=in;
      data_step++;
      data_step%=cap;
      sem_post(&data_sem);      //V操作
    }

    void PopData(mask& out)
    {
      sem_wait(&data_sem);
      out=ring_queue[space_step];
      space_step++;
      space_step%=cap;
      sem_post(&space_sem);
    }
};

//生产者
  void* consumer(void* rqueue)
  {
    RingQueue* rq=(RingQueue*)rqueue;
    while(true)
    {
      int x=rand()%50+1;
      mask m(x);
      std::cout<<"pthread_id:"<<pthread_self()<<"  mask: "<<x <<std::endl;
      rq->PushData(m);
      //sleep(1);
    }
  }

//消费者
  void* productor(void* rqueue)
{
  RingQueue* rq=(RingQueue*)rqueue;
  while(true)
  {
    mask m;
    rq->PopData(m);
    m.squre();
    sleep(1);
  }
}

