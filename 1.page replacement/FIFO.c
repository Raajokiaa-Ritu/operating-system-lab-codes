/*
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
page_fault = 15

3
6
5 7 5 6 7 3
page_fault = 4

3
20
1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6
page_fault = 16

3
12
1 2 3 4 1 2 5 1 2 3 4 5
page fault = 9

4
13
7 0 1 2 0 3 0 4 2 3 0 3 2
page_fault = 7


3
5
4 1 2 4 5
page_fault = 4

4
5
5 4 3 2 1
page_fault = 5
*/

#include<stdio.h>
#include<conio.h>

int i,j,n,m,e,s,k,mx=-1;
int index=-1,value=0,put=0,hit_frame=0;
int frame=0, page_hit=0,page_fault=0;
int LongFrame=0,free_frame=0;
int current_value=0;

int fifo[10][100]; //MATRIX     frame x string
char FH[1000];
int f[10];

void print_fifo()
{
	for(i=0;i<=frame;i++)
	{

		for(j=0;j<=n;j++)
		{
           if(i==0 && j==0)
           {
				printf("strings: ");continue;
		   }
		   if(i!=0 && j==0)
		   {
		   	printf(" Frame_");
		   }
		   if(fifo[i][j] == -1)
           {
               printf("  ");
           }
           else printf("%d ",fifo[i][j]);
		}
		printf("\n");
	}
	printf("\t ");
	for(i=1;i<=n;i++)
    {
        printf("%c ",FH[i]); //fault,hit
    }
}

int count_f(int start)
{
   for(i=1;i<=10;i++) f[i]=1; //count array : 1 1 1  1 1
	for(i=1;i<=frame;i++)
	{
		for(k=start;k>=1;k--)
		{
			if(fifo[i][k] == fifo[i][k-1])
			{
				f[i]++;
			}
			else break;
		}
	}
	int long_frame=0;
	int mx=-1;
	for(i=1;i<=frame;i++)
	{
		if(mx < f[i])
		{
			mx = f[i];
			long_frame = i;
		}
	}
	return long_frame; //index
}
int check_pageHit(int start_index,int vl)
{
	for(i=1;i<=frame;i++)
	{
		if(fifo[i][start_index] == vl)
		{
			return i;
		}
	}
	return -1;
}
int check_free_space(int start)
{
	for(i=1;i<=frame;i++)
	{
		if(fifo[i][start] == -1)
		{
			return i;
		}
	}
	return -1; //no free space
}

int main()
{

	printf("number of frame: \n");scanf("%d",&frame);

	printf("number of string:\n");scanf("%d",&n);
	int referenceString[n+5];
	printf("enter referenceStrings: \n");
	for(i=1;i<=n;i++)scanf("%d",&referenceString[i]);

	for(i=1;i<=frame;i++)
	{
		for(j=1;j<=n;j++)
		{
			fifo[i][j] = -1;
		}
	}

	//fifo[0][0] = 0;

	for(i=1;i<=frame;i++)
	{
		fifo[i][0] = i;
	}
	for(j=1;j<=n;j++)
        fifo[0][j] = referenceString[j];


   fifo[1][1] = referenceString[1];

   FH[1] = 'F';
   for(j=2;j<=n;j++)//n = number of string
   {
    	value = fifo[0][j];

    		//check for page hit index
    	int cnt=check_pageHit(j-1,value); //return

    	if(cnt!=-1)//page hit occurred
    	{
    	    FH[j] = 'H';
    		page_hit++;
    		for(k=1;k<=frame;k++)
    		{
    			fifo[k][j] = fifo[k][j-1]; //copy before column
    		}
    	}
    	else if(check_free_space(j-1) != -1) //check for free space
    	{
    	    FH[j] = 'F';
    		free_frame = check_free_space(j-1);
    		for(k=1;k<=frame;k++)
    		{
    			if(k == free_frame)
    			{
    				fifo[free_frame][j] = value;
    			}
    			else
    				fifo[k][j] = fifo[k][j-1];
    		}
    	}
    	else //check for long page frames
    	{
            FH[j] = 'F';
    		LongFrame = count_f(j-1); //long frame index
    		for(k=1;k<=frame;k++)
    		{
    			if(k == LongFrame)
    			{
    				fifo[LongFrame][j] = value;
    			}
    			else
    				fifo[k][j] = fifo[k][j-1];
    		}
    	}
   }
   printf("\n______________FIFO calculation table_____________\n\n"); print_fifo();
   page_fault = n - page_hit;
   printf("\npage_hit   = %d\npage_fault = %d",page_hit,page_fault);

   getch();

}

