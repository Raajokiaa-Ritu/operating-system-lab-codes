#include<stdio.h>
int i,j,n,m,e,s,value=0,cnt=0;
int main()
{
	printf("\nNumber of partition: ");scanf("%d",&m);
	int partition[m+4];
	for(i=1;i<=m;i++)
    {
        printf("Partition %d size = ",i);
        scanf("%d",&partition[i]);
	}

	printf("Number of process: \n");scanf("%d",&n);
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
