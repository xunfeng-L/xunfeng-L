#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 24
typedef struct node
{
    char name[10];//��ҵ��
     int arrivetime;//��ҵ����ʱ��
     int requesttime;//��ҵҪ�����ʱ��
     int starttime; //��ʼʱ��
     int finishtime; //����ʱ��
     float Ttime;//��תʱ��
     float p;//��Ӧ��
     float Wtime;//��Ȩ��תʱ��
 }JCB;

 static int N=5;  //ϵͳĬ����ҵ��
 static int flag=0;
 JCB job[MAX];

 void FCFS();//�����ȷ����㷨
 void SJF();//�����ҵ�����㷨
 void HRRN();//�����Ӧ�������㷨

 void getValue();//��ÿ����ҵ�ڵ���ز�����ֵ
 void input();//��������
 void print();//��ӡ����������б�
 void getp();//�õ���Ӧ��
 void input1();//��ʼ�����б�





 void input1()
 {
     int i;

     printf("\n--------���������Ϊ��\n");
     printf("            ��ҵ��     ����ʱ��   Ҫ�����ʱ��\n");
     for(i=0; i<N; i++)
     {
         printf("��%d����ҵ",i+1);
         printf("  %4s% 13d %14d\n",job[i].name,job[i].arrivetime,job[i].requesttime);
     }
 }

 void input()//��������
 {
     int i, jobNum, choi;
     char flag=0;
     printf("_________________________________\n");
     printf("��������ҵ������\n");
     printf("_________________________________\n");
     printf("****��������ҵ����(������2~24֮��):");
     scanf("%d", &jobNum);   //������ҵ��
     N=jobNum;
     for(i=0; i<jobNum; i++)
     {
         printf("\n��%d����ҵ��:",i+1);
         scanf(" ");
         gets(job[i].name);    //������ҵ��
         printf("����ʱ��:");
         scanf(" %d",&job[i].arrivetime);    //������ҵ�ﵽʱ��
         printf("Ҫ�����ʱ��:");
         scanf(" %d",&job[i].requesttime);    //������ҵҪ�����ʱ��
         job[i].starttime=0;

     }
     input1();
 }

 void print()//��ӡ����������б�
 {
     int i;
     float TAvetime;
     float WAvetime;
     float TtimeSum=0;
     float WtimeSum=0;

     printf("            ��ҵ��      ����ʱ��   Ҫ�����ʱ��  ��ʼʱ��  ���ʱ��  ��תʱ��  ��Ȩ��תʱ��\n");
     for(i=0; i<N; i++)
     {
        TtimeSum+=job[i].Ttime;
         WtimeSum+=job[i].Wtime;
         printf("��%d����ҵ",i+1);
         printf("  %4s% 13d %14d %9d %10d %10.2f %10.2f\n",job[i].name,job[i].arrivetime,job[i].requesttime,job[i].starttime,job[i].finishtime,job[i].Ttime,job[i].Wtime);

     }
     TAvetime=TtimeSum/N;
     WAvetime=WtimeSum/N;
     printf("ƽ����תʱ��Ϊ��%.2f",TAvetime);
     printf("\nƽ����Ȩ��תʱ��Ϊ��%.2f",WAvetime);
 }

 void choice()//ѡ������㷨
 {
     int mark;
     printf("\n\n--------------------------------------------- ");
     printf("\n        1.�����ȷ���(FCFS)�����㷨;");
     printf("\n        2.�����ҵ����(SJF)�����㷨;");
     printf("\n        3.�����Ӧ������(HRRN)�����㷨; ");
     printf("\n        4.�˳�;       ");
     printf("\n---------------------------------------------\n");
     printf("\n        ��ѡ���㷨��       ");
     scanf("%d", &mark);
     switch(mark)
     {
     case 1:
         printf("\n********************�����ȷ���(FCFS)�����㷨���*****************\n\n");
         FCFS();     //�����ȷ����㷨
         choice();
         break;
     case 2:
         printf("\n********************�����ҵ����(SJF)�����㷨���*****************\n\n");
         SJF();     //�����ҵ�����㷨
         choice();
         break;
     case 3:
         printf("\n********************�����Ӧ������(HRRN)�����㷨���*****************\n\n");
         HRRN();     //�����Ӧ�������㷨
         choice();
         break;
     case 4:
         return;
     default:
         printf("\n !!!!!!�������������ѡ��!!!!!!");
        choice();
     }
 }

 void getValue() //��ÿ����ҵ�ڵ���ز�����ֵ
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

 void FCFS()//�����ȷ����㷨
 {
     int i, j;
    JCB mark;
     for(i=0;i<N-1; i++)  //ͨ����ҵ����ʱ����������
     {
         for(j=i+1; j<N; j++)
                      {
            if(job[j].arrivetime<job[i].arrivetime)//ð������
             {
                 mark=job[j];
                 job[j]=job[i];
                job[i]=mark;
           }
        }
     }
     getValue();//��ÿ����ҵ�ڵ���ز�����ֵ
     print();  //��ӡ�����
}

 void SJF()//�����ҵ�����㷨
 {
     int i, j;
     JCB mark;
     for(i=1;i<N-1; i++)  //ͨ����ҵ��������ʱ����������
     {
        for(j=i+1; j<N; j++)
        {
             if(job[j].requesttime<job[i].requesttime)//ð������
            {
                 mark=job[j];
                 job[j]=job[i];
                 job[i]=mark;
             }
         }
     }

     getValue();  //��ÿ����ҵ�ڵ���ز�����ֵ
     print();  //��ӡ�����

 }

 void HRRN()//�����Ӧ�������㷨
 {
     int i, j;
     JCB mark;
     for(i=1;i<N-1; i++)  //ͨ������ʱ����������
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
     getp();  // �õ���Ӧ��
     print();  //��ӡ����
 }

 void getp()//�õ���Ӧ��
 {
     int i, j;
     JCB mark2;
     do{
         for(i=flag+1; i<N; i++)
         {
             if(job[i].arrivetime>job[flag].finishtime)    //��������һ���Ա�
                 job[i].starttime=job[i].arrivetime;
             else
                 job[i].starttime=job[flag].finishtime;
             job[i].finishtime=job[i].requesttime+job[i].starttime;
             job[i].Ttime=job[i].finishtime-job[i].arrivetime;
             job[i].Wtime=(float)job[i].Ttime/(float)job[i].requesttime;
         }
         for(i=flag+1;i<N-1; i++)  //�����Ԫ�� ������Ӧ���������� �õ�����Ӧ�ȵ�Ԫ��
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
     printf("\n*************************��ӭʹ����ҵ����ģ�����*************************\n\n");
     input();     //����
     choice();    //ѡ������㷨
 }