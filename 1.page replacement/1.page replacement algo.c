/*
4
13
7 0 1 2 0 3 0 4 2 3 0 3 2
page_fault = 7 //fifo
page_fault = 6  //lru
page_fault = 6  //opr
------------------------------------
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
page_fault = 15
page_fault = 12
page_fault = 9
------------------------------------------
3
6
5 7 5 6 7 3
page_fault = 4
page_fault = 4
page_fault = 4
--------------------------------------------------
3
20
1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6
page_fault = 16
page_fault = 15
page_fault = 11
---------------------------------------------------
3
12
1 2 3 4 1 2 5 1 2 3 4 5
page_fault = 9
page_fault = 10
page_fault = 7

*/

#include<stdio.h>
#include<conio.h>

int i,j,n,m,k,mx=-1,value=0;
int frame=0, page_hit=0,page_fault=0;
int LongFrame=0,free_frame=0;
int current_value=0;

int array[10][100],f[10];
int referenceString[100];
char FH[1000];

void take_input()
{
	printf("number of frame: \n");scanf("%d",&frame);
	printf("number of string:\n");scanf("%d",&n);
	printf("enter referenceStrings: \n");
	for(i=1;i<=n;i++)scanf("%d",&referenceString[i]);
}
void init()
{
	for(i=1;i<=frame;i++)
		for(j=1;j<=n;j++)
			array[i][j] = -1;

	for(i=1;i<=frame;i++)
        array[i][0] = i;
	for(j=1;j<=n;j++)
        array[0][j] = referenceString[j];

    array[1][1] = referenceString[1];

    page_fault=0;
    page_hit=0;
}
int calculate_Long_frame()
{
	int long_frame=0,mx=-1;
	for(i=1;i<=frame;i++)
    {
		if(mx < f[i])
		{
			mx = f[i];
			long_frame = i;
		}
	}
	return long_frame;
}
int count_fifo(int start)
{
    for(i=1;i<=10;i++) f[i]=1;
	for(i=1;i<=frame;i++)
	{
		for(k=start;k>=1;k--)
        {
			if(array[i][k] == array[i][k-1])f[i]++;
			else break;
		}
	}
	int long_frame = calculate_Long_frame();
	return long_frame;
}
int count_lru(int start)
{
	for(i=1;i<=frame;i++) f[i]=1;
    for(i=1;i<=frame;i++)
    {
    	current_value = array[i][start];
    	for(k=start;k>=1;k--)
    	{
    		if(array[0][k] != current_value) f[i]++;
    		else break;
    	}
    }
	int long_frame = calculate_Long_frame();
	return long_frame;
}
int count_opr(int start)
{
	for(i=1;i<=frame;i++) f[i]=1;
    for(i=1;i<=frame;i++)
    {
    	current_value = array[i][start-2];
    	for(k=start;k<=n;k++)
    	{
    		if(array[0][k] != current_value) f[i]++;
    		else break;
    	}
    }
	int long_frame = calculate_Long_frame();
	return long_frame;
}

int check_pageHit(int start_index,int vl)
{
	for(i=1;i<=frame;i++)
    {
		if(array[i][start_index] == vl) return i;
	}
	return -1;
}
int check_free_space(int start)
{
	for(i=1;i<=frame;i++)
    {
		if(array[i][start] == -1) return i;
	}
	return -1;
}

void apply_algorithm(int flag){
   FH[1] = 'F';
   for(j=2;j<=n;j++)
    {
    	value = array[0][j];
    	int cnt=check_pageHit(j-1,value);//check for page hit index
    	if(cnt!=-1)
        {//page hit occurred
    	    FH[j] = 'H';
    		page_hit++;
    		for(k=1;k<=frame;k++)
    			array[k][j] = array[k][j-1];
    	}
    	else if(check_free_space(j-1) != -1)
        {//check for free space
    	    FH[j] = 'F';
    		free_frame = check_free_space(j-1);
    		for(k=1;k<=frame;k++){
    			if(k == free_frame) array[free_frame][j] = value;
    			else array[k][j] = array[k][j-1];
    		}
    	}
    	else
        { //check for long page frames
            FH[j] = 'F';
            LongFrame=0;
            if(flag == 1)LongFrame = count_fifo(j-1);
    		if(flag == 2)LongFrame = count_lru(j-1);
            if(flag == 3)LongFrame = count_opr(j+1);

    		for(k=1;k<=frame;k++)
            {
    			if(k == LongFrame) array[LongFrame][j] = value;
    			else array[k][j] = array[k][j-1];
    		}
    	}
   }
}
void print_table(char pages[]){
	for(i=0;i<=frame;i++)
    {
		for(j=0; j<=n; j++)
		{
           if(i==0 && j==0)
           {
				printf("strings: ");continue;
		   }
		   if(i!=0 && j==0)	printf(" Frame_");
		   if(array[i][j] == -1) printf("  ");
           else printf("%d ",array[i][j]);
		}
		printf("\n");
	}
	printf("\t ");
	for(i=1;i<=n;i++) printf("%c ",pages[i]);

    page_fault = n - page_hit;
    printf("\npage_hit   = %d\npage_fault = %d",page_hit,page_fault);
}

int main()
{
   take_input();

   init();
   apply_algorithm(1); //1-fifo method
   printf("\n______________FIFO calculation table_____________\n\n");print_table(FH);

   init();
   apply_algorithm(2); //2-lru method
   printf("\n______________LRU calculation table_____________\n\n");print_table(FH);

   init();
   apply_algorithm(3); //3-opr method
   printf("\n______________OPR calculation table_____________\n\n");print_table(FH);

   getch();
}

