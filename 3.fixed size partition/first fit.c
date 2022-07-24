#include<stdio.h>
int i,j,n,m,e,s,value=0,cnt=0;

int main()
{
	printf("Number of partition: ");scanf("%d",&m);
	int partition[m+4];
	int fillup[m+4];
	for(i=1;i<=m;i++)
	{
		fillup[i] = 0; // i'th partition is not filled
	}

	for(i=1;i<=m;i++)
	{
	    printf("Partition %d size = ",i);
	    scanf("%d",&partition[i]);
	}

	printf("\nNumber of process: ");scanf("%d",&n);
	int process[n+4];

	for(i=1;i<=n;i++)
	{
        printf("Process %d need = ",i);
        scanf("%d",&process[i]);
	}
	for(i=1;i<=n;i++)
	{
		value = process[i];
		cnt = 0;
		for(j=1;j<=m;j++)
		{
			if(fillup[j] ==0 && value <= partition[j])
			{
				printf("process %d allocates partition %d.",i,j);
				printf(" Availabe space = %d\n",(partition[j]-value));
				cnt=1;
				//partition[j] = partition[j]-value;
				fillup[j] = 1;
				break;
			}
		}
		if(cnt == 0)
		{
			printf("process %d is unable to allocate any partition of memory.\n",i);
		}
	}

}
