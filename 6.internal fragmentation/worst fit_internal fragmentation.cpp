//best fit fized size partition technique for internal fragmentation
#include<bits/stdc++.h>
using namespace std;

int i,j,n,m,e,s;
int value=0,cnt=0,index=0,mn = 999999;

int main()
{

	printf("number of partition: \n");scanf("%d",&m);
	int partition[m+5];
	int fillup[m+5];

	for(i=1;i<=m;i++)scanf("%d",&partition[i]);
	for(i=1;i<=m;i++) fillup[i] = 0; //i'th partition is not filled

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
			if(fillup[j] ==0 && value<= partition[j])
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
			partition[index] -= value;
			fillup[index] = 1;
			allocated[i] = 1;
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
			printf("(Suffers from internal fragmentation).\n");
		}
	}

}
