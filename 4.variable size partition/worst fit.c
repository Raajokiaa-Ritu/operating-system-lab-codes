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
		}
		else
		{
			printf("process %d is unable to allocate any partition of memory\n",i);
		}
	}

}
