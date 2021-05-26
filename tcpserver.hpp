#pragma once 
#include<iostream>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>

class tcpserver
{
  protected:
    int _port;
    int listen_sock;

  public:
    tcpserver(int port=8080)
      :_port(port){}

    void InitServer()
    {
      signal(SIGCHLD,SIG_IGN);
      listen_sock=socket(AF_INET,SOCK_STREAM,0);
      std::cout<<"listen_sock :  "<<listen_sock<<std::endl;
      struct sockaddr_in local;
      local.sin_family=AF_INET;
      local.sin_port=htons(_port);
      local.sin_addr.s_addr=htonl(INADDR_ANY);

      if(bind(listen_sock,(sockaddr*)&local,sizeof(local))< 0 )
      {
        std::cerr << "bind error!"<<std::endl;
        exit(1);
      }

      if( listen(listen_sock,5) < 0 ) 
      {
        std::cerr<<"listen error!"<<std::endl;
        exit(2);
      }
    }

    void start()
    {
      while(true)
      {
        struct sockaddr_in accept_sock;
        socklen_t len=sizeof(accept_sock);
        int accept_fd=accept(listen_sock,(struct sockaddr*)&accept_sock,&len); 
        if( accept_fd < 0) 
        {
          std::cerr<<"accept errpr!"<<std::endl;
          exit(2);
        }
        std::cout<<"accept_fd:  "<<accept_fd<<std::endl<<" get a new link! " ; 
        std::cout<<" client ip："<< inet_ntoa (accept_sock.sin_addr ) << "  client port "<<ntohs(accept_sock.sin_port)<<std::endl;
        //单执行流：
        //service( accept_fd );

        //服务器应该能服务多个用户请求，可以用 1.多进程版本 2.多线程版本。
        //但都要注意回收进程线程，防止内存泄漏（僵尸进程），采用进程线程等待，不论是阻塞等和非阻塞等都不合理，
        //因为服务器只用来委派任务给进程线程，并不关心服务结果，服务结果由进程线程自己承担。所有采用屏蔽子进程SIG_CHILD信号或者创建孤儿进程，线程分离.方法.
        //同时注意拷贝来的文件描述符的使用，因为子进程并不需要监听_sockfd,只要accept_fd
        
        //进程版本：方法一：创建孤儿进程去执行服务例程
        //不推荐下面这种写法，fork存在失败的可能，而两次fork检测返回值繁琐。此代码未判断fork返回值
        // pid_t id=fork();
        // if(id==0)  //父进程
        // {
        //   pid_t iid=fork();
        //   if(iid==0)
        //   {
        //     //孙子进程，父进程退出后，变为孤儿进程，由1号进程回收，爷爷服务器进程不再关心此进程。
        //     close(listen_sock);
        //     service(accept_fd);
        //     exit(0);
        //   }
        //   exit(0);
        // }

        //进程版本:方法二：自定义SIGCHLD信号处理方式，父进程不需等待子进程。
        //  pid_t id=fork();
        //  if(id==0)
        //  {
        //    close(listen_sock);
        //    service(accept_fd);
        //  }
        //  else if(id < 0 )
        //  {
        //    std::cerr<<"fork() error!"<<std::endl;
        //    exit(4);        
        //  }
        //close( accept_fd );
        
        //线程版本：可以直接线程委派，也可以采用线程池。
        pthread_t id;
        //传参注意，如果主线程完成一次委派后，下一次委派开始了，但是上次委派线程还没开始运行，
        //就会错拿这次任务的文件描述符，导致信息错发。
        int *ptr=new int (accept_fd);
        pthread_create(&id,nullptr,Routine_service,(void*)ptr);
        
        //同组线程共用文件描述符表，不可关闭。
        //不进行等待线程返回释放pthread_join()，直接不关心结果，分离线程。
        //close( accept_fd );
      }
    }
    static void* Routine_service(void* arg)
    {
      pthread_detach(pthread_self());
      int * accept_fd=(int *)arg;
      service(*accept_fd);
      delete accept_fd;
      return nullptr;
    }

    static void service( int accept_fd )
    {
      char msg [1024] ;
      while( true )
      {
        msg[0]='\0';
        int size=recv(accept_fd,msg,sizeof(msg)-1,0);
        msg[size]='\0';
        if( size < 0 )
        {
          std::cerr << "read error!"<< std::endl;
          break;    
        }
        else if(size==0)
        {
          std::cout<<"client exit!"<<std::endl;
          break;
        }
        else 
        {
          std::cout<<"client #"<<msg<<std::endl;
          strcat(msg,"  server梦想是进入腾讯!");
          send(accept_fd,msg,strlen(msg),0);
        }
      }
    }

    ~tcpserver()
    {
      close(listen_sock);
    }

};
