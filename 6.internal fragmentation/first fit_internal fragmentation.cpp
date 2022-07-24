//fixed size partition suffers from internal fragmentation
#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,e,s,value=0,cnt=0;

int main()
{

	printf("\nNumber of partition: ");scanf("%d",&m);
	int partition[m+4];
	int fillup[m+4];
	for(i=1;i<=m;i++)
	{
		fillup[i] = 0; // i'th partition is not filled
	}

	printf("Enter partitions: \n");
	for(i=1;i<=m;i++)scanf("%d",&partition[i]);

	printf("Number of process: \n");scanf("%d",&n);
	int process[n+4];
	int allocated[n+4];
	for(i=1;i<=n;i++)
	{
		allocated[i] = 0; // i'th process is not allocated
	}

	//printf("Enter procesess: \n");
	for(i=1;i<=n;i++)scanf("%d",&process[i]);

	for(i=1;i<=n;i++)
	{
		value = process[i];
		cnt = 0;
		for(j=1;j<=m;j++)
		{
			if(fillup[j] ==0 && value <= partition[j])
			{
				cnt=1;
				partition[j] = partition[j]-value;
				fillup[j]    = 1;
				allocated[i] = 1;

				break;
			}
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
		if(allocated[i] == 0)
		{
			printf("But, process %d(%d kb) is unable to allocate any partition of memory.",i,process[i]);
			printf("(Suffers from internal fragmentation).\n");
		}
	}


}
