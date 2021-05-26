#pragma once 
#include<iostream>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

class tcpclient
{
  protected:
    std::string server_ip;
    int server_port;
    int sockfd;
  public:
    tcpclient(std::string ip="127.0.0.1",int port=8080)
      :server_ip(ip),server_port(port)
    {}

    void tcp_client_init()
    {
      sockfd=socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in sever;
      sever.sin_family=AF_INET;
      sever.sin_addr.s_addr=inet_addr(server_ip.c_str());
      sever.sin_port=htons(server_port);
      
      if(connect(sockfd,(struct sockaddr*)&sever,sizeof(sever))!=0)
      {
        std::cerr<<"connect error!"<<std::endl;
        exit(1);
      }
    }

    void start()
    {
      std::cout<<"please enter!"<<std::endl;
      fflush(stdout);
      while(true)
      {
        char msg[1024];
        int size=read(0,msg,sizeof(msg)-1);
        if(size>0)
        {
          msg[size-1]='\0';      //将读入的换行符抹去
          send(sockfd,msg,size,0);
          int ss=recv(sockfd,msg,sizeof(msg)-1,0);
          if(ss>0)
          {
            msg[ss]='\0';
            std::cout<< "server echo: "<< msg <<std::endl;
          }
          else if(ss==0)
          {
            //如果网络波动有可能没有收到服务器发回来的信息，
            break;
          }
          else
          {
            //recv出错，退出程序。
            break;
          }
        }
      }
    }

    ~tcpclient()
    {
      close(sockfd);
    }
};
