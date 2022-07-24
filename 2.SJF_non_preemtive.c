#include<stdio.h>

int i,j,n,m,e,sum=0;
int process[1000];
int burst_time[1000];
int gantt_chart[1000];

/*
4
1 6
2 8
3 7
4 3
*/

void find_ganttChart()
{
	gantt_chart[0] = 0;
	gantt_chart[1] = burst_time[1];

	for(i=2;i<=n;i++)
	{
		gantt_chart[i] += gantt_chart[i-1] + burst_time[i];
	}
	printf("Gantt chart : ");
	for(i=1;i<=n;i++)
	{
		printf("P%d",process[i]);
		if(i<n)printf("_>");
	}
}

void find_avgWaiting_time()
{
	float awt = 0.0;
	sum = 0;
	for(i=0;i<n;i++)
	{
		sum += gantt_chart[i];
	}

	awt = (float)sum/n;

	printf("\nAverage waiting time = %.2f\n",awt);
}

void find_avgTurnAround_time()
{
	float att = 0;
	sum = 0;
	for(i=1;i<=n;i++)
	{
		sum += gantt_chart[i];
	}

	att = (float)sum/n;

	printf("Average turn around time = %.2f\n",att);
}

int main()
{
    printf("Enter number of process = ");
	scanf("%d",&n);//process
    printf("Process _ Burst time:\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d %d",&process[i],&burst_time[i]);
	}

	for(i=1;i<n;i++)
	{
		int position=i;
		for(j=i+1;j<=n;j++)
		{
			if(burst_time[j]< burst_time[position])
				position = j;
		}

		int a = burst_time[i];//6
		int b = burst_time[position];//3

		int x = process[i];//1
		int y = process[position];//4

		burst_time[i] = b;
		burst_time[position] = a;

		process[i] = y;
		process[position] = x;

	}

	find_ganttChart();
	find_avgWaiting_time();
	find_avgTurnAround_time();

}
