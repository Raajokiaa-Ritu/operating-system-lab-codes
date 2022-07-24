//variable size partition suffers from external fragmentation
#include<stdio.h>
int i,j,n,m,e,s,value=0,cnt=0;

int main()
{
	printf("\nNumber of partition: ");scanf("%d",&m);
	int partition[m+4];

	printf("Enter partitions: \n");
	for(i=1;i<=m;i++)scanf("%d",&partition[i]);

	printf("Number of process: \n");scanf("%d",&n);
	int process[n+4];

	for(i=1;i<=n;i++)scanf("%d",&process[i]);

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

	printf("first fit algorithm\navailabe space for\n");
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
		if(allocated[i] == 0 && process[i]<=value)
		{
			printf("But, process %d(%d kb) is unable to allocate any partition of memory.",i,process[i]);
			printf("(Suffers from external fragmentation).\n");
		}
	}


}
