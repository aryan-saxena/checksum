#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char data[100];

int rightSum(int l)
{
  int sum=0, i=1;
  for(;i<l;i=i+2)
    sum=sum + (int) data[i];
  return sum;
}

int leftSum(int l)
{
  int sum=0, i=0;
  for(;i<l;i=i+2)
    sum=sum + (int) data[i];
  return sum;
}

int main() 
{
  char buf[100];
  int i, n, op=0, irs=0, ils=0, prs=0, cls=0, wc=0, pls=0, s=0, ocs=0, len=0;
  while(op==0)
  {
    printf("*** Checksum Program ***\n\n1. Sender\n2. Receiver\n3. Exit\nEnter your choice...");
    scanf("%d",&n);
    switch(n)
    {
      case 1:
      {
        printf("\nEnter the data to be transmitted -> ");
        gets(buf);
        gets(data);
        len=strlen(data);
        if(len%2!=0)
        len++;
        irs=rightSum(len);       //initial right sum
        prs=irs%256;          //partial right sum
        cls=irs/256;          //carry to left sum
        ils=cls+leftSum(len);    //initial left sum
        pls=ils%256;          //partial left sum
        wc=ils/256;           //Wrapping carry
        s=pls*256+prs+wc;
        ocs = 65535 - s;
        printf("The checksum generated is %X\n", ocs);
      }
      break;
      case 2:
      {
        char cs[100];
        int ch[100];
        printf("\nEnter the data received -> ");
        gets(buf);
        gets(data);
        printf("\nEnter the received checksum -> ");
        gets(cs);
        len=strlen(data);
        if(len%2!=0)
        len++;
        for(i=0;i<strlen(cs);i++)
        {
          if(cs[i]>='0' && cs[i]<='9')
          ch[i]=cs[i]-48;
          else if(cs[i]>='A' && cs[i]<='F')
          ch[i]=cs[i]-55;
          else if(cs[i]>='a' && cs[i]<='f')
          ch[i]=cs[i]-87;
        } 
        irs=rightSum(len) + ch[2]*16 + ch[3];       //initial right sum
        prs=irs%256;          //partial right sum
        cls=irs/256;          //carry to left sum
        ils=cls+leftSum(len) + ch[0]*16 + ch[1];    //initial left sum
        pls=ils%256;          //partial left sum
        wc=ils/256;           //Wrapping carry
        s=pls*256+prs+wc;
        ocs = 65535 - s;
        if(ocs==0)
        printf("\nThe message is accepted!\n");
        else
        printf("\nThe message is rejected!\n");
      }
      break;
      case 3: exit(0);
    }
    printf("\nPress 1 to return to main menu or 0 to exit...");
    scanf("%d", &i);
    if(i==0)
    op=1;
  }  
  return 0;
}
