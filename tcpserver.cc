#include"tcpserver.hpp" 

static void Usage(std::string proc)
{
  std::cout<<"Usage:"<<std::endl;
  std::cout<<'\t'<<proc<<" port"<<std::endl;
}

int main(int argc,char* argv[])
{
  if(argc!=2)
  {
    Usage(argv[0]);
    exit(1);  
  }
  tcpserver* tcps=new tcpserver(atoi(argv[1]));
  tcps->InitServer();
  tcps->start();
  return 0;
}
