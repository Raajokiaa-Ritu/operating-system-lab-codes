#include<stdio.h>

/*
3 4
1 24
2 3
3 3

3 2
1 10
2 5
3 8

*/

int min(int a,int b)
{
	if(a<b)return a;
	return b;
}
int process[100];
int burst_time[100];
int gantt_chart[100];
int value[100];

int i,j,n,tq,sum=0,cnt=1,check=0,siz=0,p,b,indx=1;
double avg_waitingTime = 0;
double avg_TurnAroundTime = 0;
int wt=0,tt=0;

int start[100],finish[100];

int main()
{

    printf("Number of Process & Time quantum: \n");
    scanf("%d%d",&n,&tq); // process , time quantum

    printf("enter process no. & burst time :\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d %d",&process[i],&burst_time[i]); // process, burst time
        check+=burst_time[i];
    }

    siz = (check+1)/2;

    for(j=1;j<=siz;j++)
	{

		for(i=1;i<=n;i++)
		{
			 p = process[i];
			 b = burst_time[i];
			if(b>0)
			{
				int x = min(tq,b);
				sum += x;
				burst_time[i] -=x;
				gantt_chart[cnt] = p;
				value[cnt] = sum;
				cnt++;
			}
		}
		if(sum == check)break;
	}

	printf("Gantt chart : ");
	cnt-=1;
	for(i=1;i<=cnt;i++)
	{
		printf("P%d",gantt_chart[i]);
		if(i<cnt)printf("_>");
	}
	printf("\n");

    for(p=1;p<=n;p++)
    {
        indx=1;
        for(i=1;i<=cnt;i++)
        {
            if(gantt_chart[i] == p)
            {

              start[indx] = value[i-1];
              finish[indx]= value[i];
              indx++;
            }
        }
        indx-=1;
        wt = start[1];
        for(i=2;i<=indx;i++)
        {
            wt+=start[i]-finish[i-1];
        }
        tt=0;
        for(i=cnt;i>=1;i--)
        {
            if(gantt_chart[i]==p)
            {
                tt = value[i];break;
            }
        }

        avg_waitingTime+=wt;
        avg_TurnAroundTime+=tt;

        for(i=1;i<=indx;i++)
        {
            start[i] = 0;finish[i]=0;
        }
    }

    avg_waitingTime = (double)avg_waitingTime/n;
    avg_TurnAroundTime = (double)avg_TurnAroundTime/n;
    printf("average waiting time = %.2lf\n",avg_waitingTime);
    printf("average turn around time = %.2lf\n",avg_TurnAroundTime);


}
