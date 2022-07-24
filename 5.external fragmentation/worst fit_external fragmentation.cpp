//worst fit variable size partition technique
#include<stdio.h>
int i,j,n,m,e,s;
int value=0,cnt=0,index=0,mn = 999999;

int main()
{

	printf("number of partition: \n");
	scanf("%d",&m);
	int partition[m+5];

	for(i=1;i<=m;i++)scanf("%d",&partition[i]);

	printf("number of process: \n");scanf("%d",&n);
	int process[n+5];
	int allocated[n+5];

	for(i=1;i<=n;i++) allocated[i] = 0; //i'th process is not allocated
	for(i=1;i<=n;i++)scanf("%d",&process[i]);

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
			allocated[i] = 1;
		}
		else
		{
			printf("process %d is unable to allocate any partition of memory\n",i);
		}

	}

	printf("worst fit algorithm\navailabe space for\n");
	for(i=1;i<=m;i++)
	{
		printf("partition %d = %d kb\n",i,partition[i]);
	}
	value = 0;
	printf("total availabe space=(");
	for(i=1;i<=m;i++)
	{
		printf("%d",partition[i]); value+=partition[i];
		if(i<m)printf("+");
		if(i==m)printf(")=%d kb\n",value);
	}
	for(i=1;i<=n;i++)
	{
		if(allocated[i] == 0)
		{
			printf("But, process %d(%d kb) is unable to allocate any partition of memory.",i,process[i]);
			printf("(Suffers from external fragmentation).\n");
		}
	}

}
