#include<stdio.h>

/*
3
1 24
2 3
3 3
*/

int process[1000],burst_time[1000];
int gantt_chart[1000];
int arrival_time[1000];

int i,n,j;
double average_waiting=0,average_turnAround=0;

void selection_sort()
{
	for(i=1;i<n;i++)
	{
		int position=i; //2
		for(j=i+1;j<=n;j++)
		{
			if(arrival_time[j]< arrival_time[position])//0<1
				position = j; //
		}
		int a = arrival_time[i];//2
		int b = arrival_time[position];//0

		arrival_time[i] = b;
		arrival_time[position] = a;

		int x = process[i];//1
		int y = process[position];//4

		int c = burst_time[i];
		int d = burst_time[position];

		burst_time[i] = d;
		burst_time[position] = c;

		process[i] = y;
		process[position] = x;


	}
}

void calculate_ganttChart()
{
    gantt_chart[0]=0;
    gantt_chart[1]=burst_time[1];
    for(i=2;i<=n;i++)
    {
        gantt_chart[i]=gantt_chart[i-1]+burst_time[i];
    }
    printf("\ngantt_chart : ");
    for(i=1;i<=n;i++){
        printf("P%d",process[i]);
        if(i<n)printf("_>");
    }
}
void find_Waiting_Time()
{
    printf("\n");
    for(i=0;i<n;i++)
    {
        average_waiting += (gantt_chart[i] - arrival_time[i+1]);
    }

}
//0 24 27 30
void find_TurnAround_Time()
{
    for(i=1;i<=n;i++)
    {
        average_turnAround+=(gantt_chart[i]-arrival_time[i]);
    }

}

int main()
{
    printf("Enter number of process= ");
    scanf("%d",&n);
    printf("Process   Burst_time   Arrival_time :\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d %d %d",&process[i],&burst_time[i],&arrival_time[i]);
    }
    selection_sort();
    calculate_ganttChart();
    find_Waiting_Time();
    find_TurnAround_Time();

    printf("\naverage_waiting time : %.2lf\n",(average_waiting/n));
    printf("average_turnAround time : %.2lf\n",(average_turnAround/n));
}
