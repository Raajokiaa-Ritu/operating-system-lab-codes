//variable size partition suffers from external fragmentation
#include<stdio.h>
int i,j,n,m,e,s,value=0,cnt=0,mn=0,index=-1,button;
int partition[100];
int process[100];
int allocated[100];
int copy_partition[100];

void take_input()
{
	printf("\nNumber of partition: ");scanf("%d",&m);
	for(i=1;i<=m;i++)
    {
        printf("Partition %d size = ",i);
        scanf("%d",&partition[i]);
        copy_partition[i] = partition[i];
	}

	printf("Number of process: \n");scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("Process %d need = ",i);
        scanf("%d",&process[i]);
    }
}

void init()
{
	for(i=1;i<=n;i++)
	{
		allocated[i] = 0; // i'th process is not allocated
	}
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
				cnt=1;
				partition[j] = partition[j]-value;
				allocated[i] = 1;

				break;
			}
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
			partition[index] -= value;
			allocated[i] = 1;
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
		if(cnt ==1)
        {
			partition[index] -= value;
			allocated[i] = 1;
		}
	}
}
void fragmentation()
{
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
int main()
{
    take_input();
    printf("\n");

    while(1)
    {
            printf("First fit algorithm = 1\n");
            printf("Best fit algorithm = 2\n");
            printf("Worst fit algorithm = 3\n");
            printf("exit = 4\n");
            printf("enter your choice(which algorithm do you want to apply? ) = ");
            scanf("%d",&button);

            if(button == 1)
            {
                    printf("\n\nfirst fit algorithm\navailabe space for:\n");
                    init();
                    first_fit();
                    fragmentation();
                    printf("\n");
            }
            else if(button == 2)
            {
                    printf("\n\nbest fit algorithm\navailabe space for:\n");
                    init();
                    best_fit();
                    fragmentation();
                    printf("\n");
            }
            else if(button == 3)
            {
                    printf("\n\nworst fit algorithm\navailabe space for:\n");
                    init();
                    worst_fit();
                    fragmentation();
                    printf("\n");
            }
            else{
                return 0;
            }
    }

}
