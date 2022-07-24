#include<stdio.h>
int i,j,n,m,e,s,value=0,cnt=0,mn=0,index=-1;
int partition[100];
int process[100];
int copy_partition[100];

void take_input()
{
    printf("Number of partition: ");scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
	    printf("Partition %d size = ",i);
	    scanf("%d",&partition[i]);
	    copy_partition[i] = partition[i];
	}
	printf("\nNumber of process: ");scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
        printf("Process %d need = ",i);
        scanf("%d",&process[i]);
	}
}
void init()
{
    for(i=1;i<=m;i++)
    {
        partition[i] = copy_partition[i];
    }
}
void first_fit()
{
   for(i=1;i<=n;i++)
	{
		value = process[i];
		cnt = 0;
		for(j=1;j<=m;j++)
		{
			if(partition[j]!=0 && value <= partition[j])
			{
				printf("process %d allocates partition %d.",i,j);
				printf(" Availabe space = %d\n",(partition[j]-value));
				cnt=1;
				partition[j] = partition[j]-value;
				break;
			}
		}
		if(cnt == 0)
		{
			printf("process %d is unable to allocate any partition of memory\n",i);
		}
	}
}
void best_fit()
{
   for(i=1;i<=n;i++)
	{
		value = process[i];
		cnt = 0;
		mn = 999999;
		index=-1;
		for(j=1;j<=m;j++)
		{
			if(partition[j]!=0 && value<= partition[j])
			{
				if(partition[j] < mn)
				{
					cnt = 1;
					mn = partition[j];
					index = j;
				}
			}
		}
		if(cnt ==1) {
			printf("process %d is allocated to partition %d .",i,index);
			printf("available space=%d\n",mn - value);
			partition[index] -= value;
		}
		else
		{
			printf("process %d is unable to allocate any partition of memory\n",i);
		}
    }
}
void worst_fit()
{
   	for(i=1;i<=n;i++)
	{
		value = process[i];
		cnt = 0;
		mn = -1;
		index=-1;
		for(j=1;j<=m;j++)
		{
			if(partition[j]!=0 && value<= partition[j])
			{
				if(partition[j] > mn)
				{
					cnt = 1;
					mn = partition[j];
					index = j;
				}
			}
		}
		if(cnt ==1) {
			printf("process %d is allocated to partition %d .",i,index);
			printf("available space=%d\n",mn - value);
			partition[index] -= value;
		}
		else
		{
			printf("process %d is unable to allocate any partition of memory\n",i);
		}
	}
}
int main()
{
    take_input();

    init();
    printf("\nfirst fit variable size allocation:\n\n");
    first_fit();printf("\n\n");

    init();
    printf("\nbest fit variable size allocation:\n\n");
    best_fit();printf("\n\n");

    init();
    printf("\nworst fit variable size allocation:\n\n");
    worst_fit();printf("\n\n");
}
