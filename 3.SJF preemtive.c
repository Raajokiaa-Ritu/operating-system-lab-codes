#include<stdio.h>

/*
4
1 7 0
2 4 2
3 1 4
4 4 5

5
1 4 0
2 2 1
3 8 2
4 1 3
5 9 4

3
1 9 0
2 4 1
3 9 2

4
1 8 0
2 4 1
3 9 2
4 5 3
*/

int i,j,k,n,m=0,x1=0,x2=0,arrival,maxValue=0,cnt=0,check=0,min=999999, proc = 0,burst_sum=0,cmt=0;
int process[1000];
int burst_time[1000];
int arrival_time[1000];
int arrival_time1[1000];

int gantt_chart[1000];
int gantt_value[1000];

int instant[1000],p=1;

double avg_wt=0.0;
double avg_tt=0.0;
double f;
int sum1=0,sum2=0;

void find_ganttChart()
{
      int value[burst_sum];
      maxValue = arrival_time[n];
      for(arrival = 0; arrival<maxValue; arrival++)
      {
          check = arrival;
          min = 999999;

          for(i=1; i<=n; i++)
          {
              if(check == arrival_time[i])
              {
                  arrival_time[i]+=1;
                  if(burst_time[i]>0 && burst_time[i] < min)
                  {
                      min = burst_time[i];
                      proc = process[i];
                  }
              }
          }
          burst_time[proc] -= 1;
          value[cnt] = proc; cnt++;
      }

      for(i=1;i<=n ; i++)
      {
          if(burst_time[i]>0) m++;
      }

      for(i=1; i<=m ; i++)
      {
          min = 99999;
          for(j=1; j<=n ;j++)
          {
              if(burst_time[j]>0 && burst_time[j]<min)
              {
                  min = burst_time[j];
                  proc = process[j];
              }
          }
          for(k=1;k<=min;k++)
          {
            value[cnt] = proc;cnt++;
          }

          burst_time[proc] = 0;
      }
///  p1 p2 p2 p2 p2 p4 p1 p3
      burst_sum = 0;
      printf("\n\n");
      cmt=1;
      gantt_chart[x2] = 0;
      x2++;
      for(i=0;i<cnt;i++)
      {
          if(value[i] == value[i+1])
          {
              cmt++;
          }
          else{
              gantt_chart[x1] = value[i]; ///process
              gantt_value[x2] = cmt;    ///value
              cmt++;x1++;x2++;
          }
      }
      if(cmt>0)
      {
          gantt_chart[x1] = value[i];
          gantt_value[x2] = cmt;
          x1++;x2++;
      }

      printf("Gantt Chart : ");
      for(i=0;i<x1-1;i++)
      {
          printf("P%d",gantt_chart[i]);
          if(i<x1-2)printf("_>");
      }
///0 1 5 10 17 26
    printf("\n");
    for(i=1; i<=n; i++)
    {
        for(j=1;j<=1000;j++)instant[j]=0;
        p = 1;
        for(j = 0; j<=x1; j++)
        {
            if(gantt_chart[j] == i) //i= process
            {
                instant[p]   = gantt_value[j];
                p++;
                instant[p] = gantt_value[j+1];
                p++;
            }
        }///0 1 10 17
        p-=1;
        sum1 += instant[1] - arrival_time1[i]; //avg time
        sum2 += instant[p] - arrival_time1[i];//turn arnd time

        for(j=2;j<=p-2;j++)
        {
            sum1+= instant[j+1] - instant[j];
        }

    }

    f = sum1;
    avg_wt =(double) f / n;
    printf("average waiting time : %lf\n",avg_wt);


    //----------- turn around time
    f = sum2;
    avg_tt = (double)f / n;
    printf("average turn around time : %lf\n", avg_tt);


}

int main()
{
      printf("Enter number of process= ");
      scanf("%d",&n); //number of process
      printf("\nProcess _ Burst time  _ Arrival time:\n");
      for(i=1;i<=n;i++) // process, burst_time, arrival_time
      {
          scanf("%d %d %d", &process[i], &burst_time[i], &arrival_time[i]);
          arrival_time1[i] = arrival_time[i];
          burst_sum += burst_time[i];
      }
      find_ganttChart();

}
