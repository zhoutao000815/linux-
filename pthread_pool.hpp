#pragma once 
#include<iostream>
#include<pthread.h>
#include<queue>
#include<unistd.h>

template <class T1>
class mask
{
  public:
    mask(){}

    mask(T1 a,T1 b)
      :data1(a),data2(b)
    {}

    T1 Add()
    {
      T1 rel=data1+data2;
      std::cout <<"thread is[" << pthread_self() << "] mask run ... done: base# " ;
      std::cout<<data1<<" + "<<data2<<" = "<<rel<<std::endl;
      return rel;
    }

  protected:
    T1 data1;
    T1 data2;
};

template <class T>
class pthread_pool
{
  public:
    pthread_pool(int maxnum=6,bool q=false)
      :_poolmax(maxnum),quit(q)
    {}

    ~pthread_pool()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&empty);
    }

    void push(T& in)
    {
      lock_queue();
      pool.push(&in);
      unlock_queue();
      //notice_consumer();
      notice_all_consumer();
    }

    void get_rel(T& out)  //这里不再需要上锁，因为获取数据的地方在线程调用的Run里，线程已经在Run函数里上好锁排好队了。
    {
      //lock_queue();
      out=*pool.front();
      pool.pop();
      //unlock_queue();
    }

    static void* Run(void* arg)  //由于C++成员函数第一个参数是隐藏的this指针，不符合pthread_create的第三个函数指针的参数，所以定义为静态成员函数去掉this指针。同时传参传this指针，方便访问使用成员
    {
      pthread_pool* this_p=(pthread_pool*)arg;
      while(!this_p->quit)
      {
        usleep(2500);
        this_p->lock_queue();
        while(!this_p->quit && this_p->cond_empty())  //当线程池为空时，线程都在cond_empty这个条件变量和锁内部，成队列等待，
          //唤醒可以一群唤醒（惊群效应）pthread_cond_broadcast()，也可以一个一个唤醒pthread_cond_signal()
        {
          this_p->wait_consumer();
        }
        T m;
        if(!this_p->quit && !this_p->pool.empty())
        {
          this_p->get_rel(m);
        }
        this_p->unlock_queue();
        m.Add();
      }
    }

    void quit_pthread_pool()
    {
      if(!pool.empty())
      {
        std::cout<<"仍有任务在运行！  "<<std::endl;
        return ;
      }
      quit =true;
      notice_all_consumer();
    }

    void Init()
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&empty,nullptr);
      pthread_t t;
      for(int i=0;i<_poolmax;i++)
      {
        pthread_create(&t,nullptr,Run,this);
      }
    }

  protected:
    std::queue<T*> pool;
    int _poolmax;
    pthread_mutex_t lock;
    pthread_cond_t empty;
    bool quit;

  private:
    void lock_queue()
    {
      pthread_mutex_lock(&lock);
    }

    void unlock_queue()
    {
      pthread_mutex_unlock(&lock);
    }

    bool cond_empty()
    {
      return pool.empty();
    }

    void wait_consumer()
    {
      pthread_cond_wait(&empty,&lock);
    }

    void notice_consumer()
    {
      pthread_cond_signal(&empty);
    }
    void  notice_all_consumer()
    {
      pthread_cond_broadcast(&empty);
    }
};
