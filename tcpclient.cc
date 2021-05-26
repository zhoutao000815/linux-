#include"tcpclient.hpp" 

static void Usage(std::string proc)
{
  std::cout<<"Usage:"<<std::endl;
  std::cout<<'\t'<<proc<<" ip "<<" port"<<std::endl;
}

int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
    exit(1);  
  }
  tcpclient* tcps=new tcpclient(argv[1],atoi(argv[2]));
  tcps->tcp_client_init();
  tcps->start();
  return 0;
}
