#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
#include<unistd.h>

class mask
{
  public:
    int left;
    int right;
  public:
    mask(int a=0,int b=0)
    {
      left=a;
      right=b;
    }

    int add()
    {
      int c=left+right;
      std::cout<<left<<"+"<<right<<"="<<c<<std::endl;
      return c;
    }
};

template<class T>
class block_queue
{
  private:
    std::queue<T> q;
    int cap;
    pthread_mutex_t lock;
    pthread_cond_t empty;
    pthread_cond_t full;
    
    void lock_queue()
    {
      pthread_mutex_lock(&lock);
    }

    void unlock_queue()
    {
      pthread_mutex_unlock(&lock);
    }
    
    bool Is_full()
    {
      return q.size()==cap?true:false;
    }

    bool Is_empty()
    {
      return q.empty();
    }

    void wait_productor()
    {
      pthread_cond_wait(&full,&lock);
    }

    void notice_consumer()
    {
      pthread_cond_signal(&empty);
    }

    void wait_consumer()
    {
      pthread_cond_wait(&empty,&lock);
    }

    void notice_productor()
    {
      pthread_cond_signal(&full);
    }

  public:
    
    block_queue()
    {
      //不要在这里初始化，如果初始化的某个函数出错退出了。那这个对象有没有被创建出来?未知！！！让调用者生成对象后手动初始化。
    }
    
    void init()
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&empty,nullptr);
      pthread_cond_init(&full,nullptr);
      cap=8;
    }

    ~block_queue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&full);
      pthread_cond_destroy(&empty);
    }
    
    void push(const T& in)
    {
      lock_queue(); 
      while(Is_full())
      {
        notice_consumer();
        wait_productor();
      }
      q.push(in);
      notice_consumer();
      unlock_queue();
    }
    
    void pop(T& out)
    {
      lock_queue();
      while(Is_empty())
      {
        notice_productor();
        wait_consumer();
      }
      out=q.front();
      q.pop();
      notice_productor();
      unlock_queue();
    }

};
