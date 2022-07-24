#include<stdio.h>
#include <stdbool.h>
int i,j,n,m,e,s,index=1,k;
int p,r ;
int safe_process=0;
int allocation[10+1][10+1];
int maximumNeed[10+1][10+1];
int banker[10][30];
int safe_sequence[20];
int cnt=0,total_process=0;
char saved_type[100];
char ch;

void print_banker()
{
	printf("Process allocation  maximumNeed  \tavailable  \tremaining need\n");
	printf("\t");
	for(i=0;i<1;i++)
    {
        cnt = 0;
        for(j=1;j<=4*r;j++)
        {
            ch = saved_type[cnt];
            printf("%c ",ch);
            cnt+=2;
            if(j==r || j==r+r || j==r+r+r || j==r+r+r+r)
            {
                cnt = 0;
                printf("\t");
            }

        }
    }
    printf("\n");
	for(int k=1;k<=p+1;k++)
	{
		printf("P%d\t",k);
		for(j=1;j<=r+r+r+r;j++)
		{
			printf("%d ",banker[k][j]);
			if(j==r || j==r+r || j==r+r+r)
				printf("\t");
		}
		printf("\n");
	}
	printf("\n");
}
void print_safeSequence()
{
	printf("safe_sequence: ");
	for(i=1;i<=p;i++)
	{
		printf("P%d ",safe_sequence[i]);
		if(i<p)printf("-> ");
	}
	printf("\n\n");
}

int main()
{
    printf("Number of process: ");
	scanf("%d",&p);
	printf("Number of resources: ");
	scanf("%d",&r);

	printf("enter resource type: ");
	getchar();
    for(i=0;i<2*r-1;i++)
    {
        scanf("%c",&saved_type[i]);
    }
    printf("\n");
    printf("total number of resource for each type: ");
    for(i=1;i<=r;i++)
    {
        int s;
        scanf("%d",&s);
    }
	printf("available resource: ");
	for(i=1;i<=r;i++)
	{
		scanf("%d",&banker[1][i+r+r]);
	}
    printf("allocated resources: \n");
	for(i=1;i<=p;i++)
	{
		for(j=1;j<=r;j++)
		{
			scanf("%d",&allocation[i][j]);
			banker[i][j] = allocation[i][j];
		}
	}
	printf("\nmaximum resoruce Need:\n");
	for(i=1;i<=p;i++)
	{
		for(j=1;j<=r;j++)
		{
			scanf("%d",&maximumNeed[i][j]);
			banker[i][j+r] = maximumNeed[i][j];//r = resource
		}
	}

	printf("\n---------Remaining need matrix----------\n");
    for(i=1;i<=p;i++)
	{
		for(j=1;j<=r;j++)
		{
			if(maximumNeed[i][j] - allocation[i][j]>=0)
			banker[i][j+r+r+r] = maximumNeed[i][j] - allocation[i][j];
		    else banker[i][j+r+r+r] = 0;
		}
	}
	printf("\n");print_banker(); printf("\n");

	int pos = 1; int occupied[p+1];
	for(i=1;i<=p;i++)occupied[i] = 0;

	bool upgrade=false;

	for(int track=1; track<=p; track++)//p =process
	{
		for(int process=pos; process<= p; process++) //3 4 5
		{
		    upgrade = false;
			if(occupied[process] == 0)
			{
				cnt=0;
				for(j=r+r+r+1; j<= r+r+r+r; j++)
				{
					if(banker[track][j-r] >= banker[process][j])cnt++;
					else break;
				}
				if(cnt == r)//r =resource
				{
					total_process++;
					safe_process = process;
					safe_sequence[index] = safe_process;index++;
					occupied[safe_process] = 1;
					upgrade = true;
					for(j=r+r+1; j<=r+r+r; j++)
					{
						int sum = banker[track][j] + banker[safe_process][j-r-r];
						banker[track+1][j] = sum;
					}
				}
			}
			if(upgrade == true){
				pos = safe_process+1;
				if(pos>p)pos=1;
				break;
			}
		}
	}
	if(total_process == p)
	{
		printf("\n ---------Banker alogrithm table---------\n\n");
		print_banker();printf("\n");
		print_safeSequence();
	}

	else
	{
		printf("Deadlock occured!");
	}
}
/*
5 //process
4 //resources
enter resource type: m n o p
total resource for each type:8 5 9 7
available resource: 1 2 2 2
//allocated resource
2 0 1 1
0 1 2 1
4 0 0 3
0 2 1 0
1 0 3 0

//maximum resource need
3 2 1 4
0 2 5 2
5 1 0 5
1 5 3 0
3 0 3 3

ans:P2  ->  P4  ->  P0  ->  P1  ->  P3
    :p3->p5->p1->p2->p4
---------------
Enter the Number of Process  :  5
Enter the Number of Resource  :  4
Enter  total  Resources:
9 13 10 11
Enter  allocated  resources  for processors :
4 0 0 1
1 1 0 0
1 2 5 4
0 6 3 3
1 4 1 2
Enter  Max_Need  resources  for processors :
6 0 1 2
1 7 6 0
2 3 5 6
1 6 5 3
1 6 5 6
ans:deadlock
---------------
5 //process
3//resource
enter resource type: a b c
total number of resource for each type:7 2 6
available resource: 0 0 0
//allocated resources:
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2

//maximum resoruce Need:
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
------------

*/
