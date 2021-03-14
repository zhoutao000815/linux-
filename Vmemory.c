#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int g_val = 0;
int main()
{
  pid_t id = fork();
  if(id < 0)
  {
    perror("fork");
    return 0;
  }
  else if(id == 0)
  {
  //child 
  g_val=1000;
  printf("child[%d]: %d : %p\n", getpid(), g_val, &g_val);
  }else
  //parent
  {
  printf("parent[%d]: %d : %p\n", getpid(), g_val, &g_val);
  }
  sleep(1);
  return 0;
}
