#include <stdio.h>
#include <stdlib.h>
#define N 25
void input();
void fcfs();
void hrrf();
void sjf();
void quit();
int Menu();
int i,k,num,m,n;
struct JCB{
    char name[10];            //作业名
    float arrivetime;         //作业提交时间
    float runtime;            //作业运行时间
    float run;                //开始时间
    float finish;             //完成时刻
    float T;                  //周转时间
    float W;                  //带权周转时间
}jcb[N],temp;


void main()
{
    int choic,n;
    input(n);
    while(1)
    {
        choic=Menu();
        switch(choic)
        {
            case 1:
                fcfs(n);
                break;
            case 2:
                sjf(n);
                break;
            case 3:
                hrrf(n);
                break;
            case 4:
                quit();
                break;
        }
    }
}

int Menu()
{
    int choic;
    printf("1.先来先服务（FCFS）调度算法\n");
    printf("2.短作业优先 (SJF) 调度算法\n");
    printf("3.响应比高者优先(HRRN)调度算法\n");
    printf("4.退出系统\n");
    printf("请选择菜单号(1——4):");
    while((!scanf("%d",&choic))||choic<1||choic>4)
    {
        getchar();
        printf("\n输入错误!!!!!!请重新输入\n");

    }
    return choic;
}
void input() // 建立作业控制块函数
{
    int i;
    printf("请输入作业个数(2～24):");
    while(!scanf("%d",&num)||num<2||num>24)
    {
        getchar();
        printf("输入错误------->请重新输入\n");
        printf("\n");
        printf("请输入作业个数(2～24):");
    }

    printf("\n");
    for(i=0;i<num;i++){
        printf("\t第%d个作业名:",i+1);
        scanf("%s",&jcb[i].name);
        printf("\t请输入作业提交时间:");
        scanf("%f",&jcb[i].arrivetime);
        printf("\t请输入作业运行时间:");
        scanf("%f",&jcb[i].runtime);
        printf("\n");
    }
}


void quit()
{
    printf("谢谢使用该系统!\n");
    exit(0);
}

void output()
{
    float numT=0,numW=0,avgT=0,avgW=0;
    printf("-----------------------------------------------------------------------\n");
    printf(" 作业名  提交时间  运行时间  开始时间  完成时间  周转时间  带权周转时间\n");
    for(i=0;i<num;i++)
    {
        printf("   %-8s%-10.2f%-10.2f%-10.2f%-10.2f%-10.2f%-10.2f",jcb[i].name,jcb[i].arrivetime,jcb[i].runtime,jcb[i].run,jcb[i].finish,jcb[i].T,jcb[i].W);
        printf("\n");
        numT=numT+jcb[i].T;
        numW=numW+jcb[i].W;
    }
    printf("-----------------------------------------------------------------------\n");
    avgT=numT/num;
    avgW=numW/num;
    printf("平均作业周转时间：%.2f\n",avgT);
    printf("\n");
    printf("平均带权作业周转时间：%.2f\n",avgW);
    printf("\n");
}
void sort()
{
    int i,j;
    for(j=0;j<num;j++)/*冒泡排序*/
    {
        for(i=0;i<num-j-1;i++)
        {
            if(jcb[i].arrivetime>jcb[i+1].arrivetime)
            {
                temp=jcb[i];
                jcb[i]=jcb[i+1];
                jcb[i+1]=temp;
            }
        }
    }
}
void running()
{
    for(k=0;k<num;k++)
    {
        if(k==0)/*运行第一个作业*/
        {
            jcb[k].run=jcb[k].arrivetime;
            jcb[k].finish=jcb[k].arrivetime+jcb[k].runtime;
        }
        else
        {
            if(jcb[k].arrivetime>=jcb[k-1].finish)/*当前作业已经结束，下一个作业还没有到达或者刚好到达*/
            {
                jcb[k].run=jcb[k].arrivetime;
                jcb[k].finish=jcb[k].arrivetime+jcb[k].runtime;
            }
            else/*当前作业未完成，下一个作业已到达*/
            {
                jcb[k].run=jcb[k-1].finish;
                jcb[k].finish=jcb[k-1].finish+jcb[k].runtime;
            }
        }

    }
    for(k=0;k<num;k++)
    {
        jcb[k].T=jcb[k].finish-jcb[k].arrivetime;
        jcb[k].W=jcb[k].T/jcb[k].runtime;
    }
}
void fcfs()/*先来先服务*/
{
    sort();
    running();
    output();/*输出作业调度表*/
}
void sjf()/*短作业优先*/
{
    int next;
    float min;/*作业运行的最小时间*/
    sort();
    for(m=0;m<num;m++)
    {
        i=0;
        if(m==0)
        {
            jcb[m].finish=jcb[m].arrivetime+jcb[m].runtime;
        }
        else
        {
            jcb[m].finish=jcb[m-1].finish+jcb[m].runtime;
        }
        for(n=m+1;n<num;n++)
        {
            if(jcb[n].arrivetime<=jcb[m].finish)//判断每次作业完成之后又有多少作业到达
                i++;
        }
        min=jcb[m+1].runtime;
        next=m+1;
        for(k=m+1;k<i;k++)//找出到达后的作业中运行时间最小的作业
        {
            if(jcb[k+1].runtime<min)
            {
                min=jcb[k+1].runtime;
                next=k+1;
                temp=jcb[m+1];
                jcb[m+1]=jcb[next];
                jcb[next]=temp;
            }
            else
            {
                min=jcb[k+1].runtime;
                next=k;
                temp=jcb[k+1];
                jcb[k+1]=jcb[next];
                jcb[next]=temp;
            }
        }
    }
    running();
    output();
}
void hrrf()/*最高响应比优先*/
{
    int flag;
    float max;//最大的响应比
    sort();
    for(m=0;m<num;m++)
    {
        i=0;
        if(m==0)
        {
            jcb[m].finish=jcb[m].arrivetime+jcb[m].runtime;
        }
        else
        {
            jcb[m].finish=jcb[m-1].finish+jcb[m].runtime;
        }
        for(n=m+1;n<num;n++)
        {
            if(jcb[n].arrivetime<=jcb[m].finish)
                i++;
        }
        max=(jcb[m].finish-jcb[m+1].arrivetime)/jcb[m+1].runtime;//响应比
        flag=m+1;
        for(k=m+1;k<i;k++)
        {
            if(max<=(jcb[k].finish-jcb[k+1].arrivetime)/jcb[k+1].runtime)//响应比大的先执行
            {
                max=(jcb[k].finish-jcb[k+1].arrivetime)/jcb[k+1].runtime;
                flag=k+1;
                temp=jcb[k];
                jcb[k]=jcb[flag];
                jcb[flag]=temp;
            }
        }
    }
    running();
    output();
}