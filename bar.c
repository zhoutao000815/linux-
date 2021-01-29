#include"bar.h"
void progressbar()
{
  char bar [barsize]={0};
  char *flag="|/-\\";
  int i=0;
  while(i<100)
  {
    bar[i++]='#';
    printf("[%-100s][%3d%%][%c]\r",bar,i,*(flag+i%4)); 
    usleep(100000);
    fflush(stdout);
  }
  printf("\n");
  return;
}
