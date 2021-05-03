#include"pthread_pool.hpp"
#include<unistd.h>
using namespace std;

int main()
{
  pthread_pool<mask<int>> pp(5);
  pp.Init();

  int count=30;
  while(count--)
  {
    int left=random()%103;
    int right=random()%103;
    mask<int> m(left,right);
    cout<<left<<" + "<<right<<" =  ? "<<endl;
    pp.push(m);
    usleep(1250);
  }
  return 0;
}
