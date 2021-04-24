#include"cp_block_queue.hpp" 
//本意是想写个处理整数加法的线程阻塞队列，万一以后会存储别的数据类型，加个模板。如果处理别的数据，生产者和消费者执行的函数，需要做修改。

//多生产者多消费者，同种之间是需要互斥的，异种之间是需要同步的。
//我们可以让同种之间组内竞争，胜者去做事，

pthread_mutex_t conlock;
pthread_mutex_t prolock;

void* product(void* bqp)
{
  block_queue<mask>* p=(block_queue<mask>*)bqp;
  while(true)
  {
    int left =rand()%100;
    int right =rand()%100;
    mask m(left,right);
    pthread_mutex_lock(&prolock);
    p->push(m);
    pthread_mutex_unlock(&prolock);
    std::cout<<"pthread_id:"<<pthread_self()<<"  left:"<<left<<"  right:"<<right<<std::endl;
    sleep(1);
  }
}

void* consume(void* bqp)
{
  block_queue<mask>* p=(block_queue<mask>*)bqp;
  while(true)
  {
    mask t;
    pthread_mutex_lock(&conlock);
    p->pop(t);
    pthread_mutex_unlock(&conlock);//尽量缩小锁住的临界区，如果锁住了一些不必要的操作，会拖缓效率。
    std::cout<<"pthread_id:"<<pthread_self()<<"     ";
    t.add();                       //将数据在任务队列取出解锁后，再进行处理，别小看这个顺序，如果单个任务执行时间很长呢?难道让其他线程等你处理完再来领任务嘛？
  }
}


int main()
{
  block_queue<mask> bq;
  bq.init();
  pthread_mutex_init(&conlock,nullptr);
  pthread_mutex_init(&prolock,nullptr);

  pthread_t t1,t2,t3,t4,t5,t6;
  pthread_create(&t1,nullptr,consume,&bq);
  pthread_create(&t2,nullptr,consume,&bq);
  pthread_create(&t3,nullptr,consume,&bq);
  pthread_create(&t4,nullptr,product,&bq);
  pthread_create(&t5,nullptr,product,&bq);
  pthread_create(&t6,nullptr,product,&bq);

  pthread_join(t1,nullptr);
  pthread_join(t2,nullptr);
  pthread_join(t3,nullptr);
  pthread_join(t4,nullptr);
  pthread_join(t5,nullptr);
  pthread_join(t6,nullptr);

  pthread_mutex_destroy(&conlock);
  pthread_mutex_destroy(&prolock);
  return 0;
}
