#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 24
typedef struct node
{
    char name[10];//作业名
     int arrivetime;//作业到达时间
     int requesttime;//作业要求服务时间
     int starttime; //开始时间
     int finishtime; //结束时间
     float Ttime;//周转时间
     float p;//响应比
     float Wtime;//带权周转时间
 }JCB;

 static int N=5;  //系统默认作业数
 static int flag=0;
 JCB job[MAX];

 void FCFS();//先来先服务算法
 void SJF();//最短作业优先算法
 void HRRN();//最高响应比优先算法

 void getValue();//给每个作业内的相关参数赋值
 void input();//输入数据
 void print();//打印输入的数据列表
 void getp();//得到响应比
 void input1();//初始数据列表





 void input1()
 {
     int i;

     printf("\n--------输入的数据为：\n");
     printf("            作业名     到达时间   要求服务时间\n");
     for(i=0; i<N; i++)
     {
         printf("第%d个作业",i+1);
         printf("  %4s% 13d %14d\n",job[i].name,job[i].arrivetime,job[i].requesttime);
     }
 }

 void input()//输入数据
 {
     int i, jobNum, choi;
     char flag=0;
     printf("_________________________________\n");
     printf("请输入作业个数：\n");
     printf("_________________________________\n");
     printf("****请输入作业个数(个数在2~24之间):");
     scanf("%d", &jobNum);   //输入作业数
     N=jobNum;
     for(i=0; i<jobNum; i++)
     {
         printf("\n第%d个作业名:",i+1);
         scanf(" ");
         gets(job[i].name);    //输入作业名
         printf("到达时间:");
         scanf(" %d",&job[i].arrivetime);    //输入作业达到时间
         printf("要求服务时间:");
         scanf(" %d",&job[i].requesttime);    //输入作业要求服务时间
         job[i].starttime=0;

     }
     input1();
 }

 void print()//打印输入的数据列表
 {
     int i;
     float TAvetime;
     float WAvetime;
     float TtimeSum=0;
     float WtimeSum=0;

     printf("            作业名      到达时间   要求服务时间  开始时间  完成时间  周转时间  带权周转时间\n");
     for(i=0; i<N; i++)
     {
        TtimeSum+=job[i].Ttime;
         WtimeSum+=job[i].Wtime;
         printf("第%d个作业",i+1);
         printf("  %4s% 13d %14d %9d %10d %10.2f %10.2f\n",job[i].name,job[i].arrivetime,job[i].requesttime,job[i].starttime,job[i].finishtime,job[i].Ttime,job[i].Wtime);

     }
     TAvetime=TtimeSum/N;
     WAvetime=WtimeSum/N;
     printf("平均周转时间为：%.2f",TAvetime);
     printf("\n平均带权周转时间为：%.2f",WAvetime);
 }

 void choice()//选择调度算法
 {
     int mark;
     printf("\n\n--------------------------------------------- ");
     printf("\n        1.先来先服务(FCFS)调度算法;");
     printf("\n        2.最短作业优先(SJF)调度算法;");
     printf("\n        3.最高响应比优先(HRRN)调度算法; ");
     printf("\n        4.退出;       ");
     printf("\n---------------------------------------------\n");
     printf("\n        请选择算法：       ");
     scanf("%d", &mark);
     switch(mark)
     {
     case 1:
         printf("\n********************先来先服务(FCFS)调度算法结果*****************\n\n");
         FCFS();     //先来先服务算法
         choice();
         break;
     case 2:
         printf("\n********************最短作业优先(SJF)调度算法结果*****************\n\n");
         SJF();     //最短作业优先算法
         choice();
         break;
     case 3:
         printf("\n********************最高响应比优先(HRRN)调度算法结果*****************\n\n");
         HRRN();     //最高响应比优先算法
         choice();
         break;
     case 4:
         return;
     default:
         printf("\n !!!!!!输入错误，请重新选择!!!!!!");
        choice();
     }
 }

 void getValue() //给每个作业内的相关参数赋值
 {
     int i;

     for(i=0; i<N; i++)
     {
         if(i==0 || job[i].arrivetime>job[i-1].finishtime)
             job[i].starttime=job[i].arrivetime;
         else
             job[i].starttime=job[i-1].finishtime;
         job[i].finishtime=job[i].requesttime+job[i].starttime;
         job[i].Ttime=(float)job[i].finishtime-(float)job[i].arrivetime;
         job[i].Wtime=(float)job[i].Ttime/(float)job[i].requesttime;

     }
 }

 void FCFS()//先来先服务算法
 {
     int i, j;
    JCB mark;
     for(i=0;i<N-1; i++)  //通过作业到达时间整体排序
     {
         for(j=i+1; j<N; j++)
                      {
            if(job[j].arrivetime<job[i].arrivetime)//冒泡排序
             {
                 mark=job[j];
                 job[j]=job[i];
                job[i]=mark;
           }
        }
     }
     getValue();//给每个作业内的相关参数赋值
     print();  //打印出结果
}

 void SJF()//最短作业优先算法
 {
     int i, j;
     JCB mark;
     for(i=1;i<N-1; i++)  //通过作业所需运行时间整体排序
     {
        for(j=i+1; j<N; j++)
        {
             if(job[j].requesttime<job[i].requesttime)//冒泡排序
            {
                 mark=job[j];
                 job[j]=job[i];
                 job[i]=mark;
             }
         }
     }

     getValue();  //给每个作业内的相关参数赋值
     print();  //打印出结果

 }

 void HRRN()//最高响应比优先算法
 {
     int i, j;
     JCB mark;
     for(i=1;i<N-1; i++)  //通过到达时间整体排序
     {
         for(j=i+1; j<N; j++)
         {
             if(job[j].arrivetime<job[i].arrivetime)
             {
                mark=job[j];
                 job[j]=job[i];
                 job[i]=mark;
             }
        }
     }
     job[0].starttime=job[0].arrivetime;
     job[0].finishtime=job[0].requesttime+job[0].starttime;;
     job[0].Ttime=job[0].finishtime-job[0].arrivetime;
     job[0].Wtime=(float)job[0].Ttime/(float)job[0].requesttime;

     flag=0;
     getp();  // 得到响应比
     print();  //打印出来
 }

 void getp()//得到响应比
 {
     int i, j;
     JCB mark2;
     do{
         for(i=flag+1; i<N; i++)
         {
             if(job[i].arrivetime>job[flag].finishtime)    //后面的与第一个对比
                 job[i].starttime=job[i].arrivetime;
             else
                 job[i].starttime=job[flag].finishtime;
             job[i].finishtime=job[i].requesttime+job[i].starttime;
             job[i].Ttime=job[i].finishtime-job[i].arrivetime;
             job[i].Wtime=(float)job[i].Ttime/(float)job[i].requesttime;
         }
         for(i=flag+1;i<N-1; i++)  //后面的元素 根据响应比整体排序 得到高响应比的元素
         {
             for(j=i+1; j<N; j++)
            {
                if(job[j].Wtime>job[i].Wtime)
                 {
                     mark2=job[j];
                     job[j]=job[i];
                     job[i]=mark2;
                }
            }
        }
         flag++;
    }while(flag<N);
 }

 void main()
 {
     printf("\n*************************欢迎使用作业调度模拟程序*************************\n\n");
     input();     //输入
     choice();    //选择调度算法
 }