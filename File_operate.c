#include<stdio.h>
#include<string.h>
int main()
{
  FILE* fp=fopen("bite","w+");
  if(!fp)
  {
    printf("fopen error! \n");
  }
  const char* str="linux so easy!";
  fwrite(str,strlen(str),1,fp);
  fseek(fp,0,SEEK_SET);
  //rewind(fp);
  char temp[1024];
  size_t i=fread(temp,1,strlen(str),fp);
  while(1)
  {
    if(i>0) 
    {
      temp[i]=0;
      printf("%s\n",temp);     
      break;
    }
    if(feof(fp))
    {
      printf("fread error\n");     
      break;
    }
  }
  fclose(fp);
  return 0; 
}
