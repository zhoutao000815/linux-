#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sigcb(int sig)
{
  printf("begin catch a sig:%d !\n",sig);
  sleep(5);
  printf("end catch a sig:%d !\n",sig);
}

void sigbitprintf(sigset_t *sig)
{
  int i=1;
  for(i=1;i<32;i++)
  {
    if(sigismember(sig,i))
    {
      printf("1");
    }
    else 
    {
      printf("0");
    }
  } 
  printf("\n");
}
int main()
{

  //signal(2,sigcb);
  
  struct sigaction zt;
  zt.sa_flags=0;
  zt.sa_handler=sigcb;
  sigaction(2,&zt,NULL);

  //sig用来设置block集，pend用来查看penging集。
  sigset_t sig, pend;
  sigemptyset(&sig);
  //sigfillset(&sig);         //这个函数是将传入的信号集：sig设置为全1。
  sigaddset(&sig,2);
  
  sigset_t osig;
  if(sigprocmask(SIG_SETMASK,&sig,&osig)==-1)
  {
    perror("sigprocmask!");
  }
  
  int i=0;
  while(1)
  {
    sigpending(&pend);
    sigbitprintf(&pend);
    if(i==10)
    {
      printf("取消屏蔽信号2！\n");
      sigprocmask(SIG_UNBLOCK,&sig,NULL);
    }
    i++;
    sleep(1);
  }
  return 0;
}
