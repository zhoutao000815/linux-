#pragma once 
#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

class udpserver
{

  protected:
    std::string _ip;
    int _port;
    int _sock;

  public:
    udpserver(std::string ip="127.0.0.1",int port=8080)
      :_ip(ip),_port(port){}

    void InitServer()
    {
      _sock=socket(AF_INET,SOCK_DGRAM,0);
      std::cout<<"sock :  "<<_sock<<std::endl;
      struct sockaddr_in local;
      local.sin_family=AF_INET;
      local.sin_port=htons(_port);
      local.sin_addr.s_addr=inet_addr(_ip.c_str());
      
      if(bind(_sock,(sockaddr*)&local,sizeof(local))<0)
      {
        std::cerr << "bind error!\n"<<std::endl;
        exit(1);
      }
    }
    
    void start()
    {
      char msg[64];
      for(;;)
      {
        msg[0]='\0';
        struct sockaddr_in end_point;
        socklen_t len=sizeof(end_point);
        ssize_t s = recvfrom(_sock,msg,sizeof(msg)-1,0,(struct sockaddr*)&end_point,&len);
        if(s>0)
        {
          msg[s]='\0';
          std::cout<<"client # "<<msg<<std::endl;
          std::string echo_string="[server echo]:  ";
          echo_string+=msg;
          sendto(_sock,echo_string.c_str(),echo_string.size(),0,(struct sockaddr*)&end_point,len);

        }
      }
    }

    ~udpserver()
    {
      close(_sock);
    }

};
