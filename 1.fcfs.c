#include<stdio.h>

/*
3
1 24
2 3
3 3
*/

int process[1000],burst_time[1000];
int gantt_chart[1000];

int i,n;
double average_waiting=0,average_turnAround=0;

void calculate_ganttChart()
{
    gantt_chart[0]=0;
    gantt_chart[1]=burst_time[1];
    for(i=2;i<=n;i++)
    {
        gantt_chart[i]=gantt_chart[i-1]+burst_time[i];
    }
    printf("gantt_chart : ");
    for(i=1;i<=n;i++){
        printf("P%d",i);
        if(i<n)printf("_>");
    }
}
void find_Waiting_Time()
{
    for(i=0;i<n;i++)
    {
        average_waiting += gantt_chart[i];
    }
}
//0 24 27 30
void find_TurnAround_Time()
{
    for(i=1;i<=n;i++)
    {
        average_turnAround+=gantt_chart[i];
    }
}

int main()
{
    printf("Enter number of process= ");
    scanf("%d",&n);
    printf("Process    -   Burst_time:\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d %d",&process[i],&burst_time[i]);
    }
    calculate_ganttChart();
    find_Waiting_Time();
    find_TurnAround_Time();

    printf("\naverage_waiting time : %.2lf\n",(average_waiting/n));
    printf("average_turnAround time : %.2lf\n",(average_turnAround/n));
}
