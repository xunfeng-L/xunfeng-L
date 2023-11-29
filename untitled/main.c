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
    char name[10];            //��ҵ��
    float arrivetime;         //��ҵ�ύʱ��
    float runtime;            //��ҵ����ʱ��
    float run;                //��ʼʱ��
    float finish;             //���ʱ��
    float T;                  //��תʱ��
    float W;                  //��Ȩ��תʱ��
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
    printf("1.�����ȷ���FCFS�������㷨\n");
    printf("2.����ҵ���� (SJF) �����㷨\n");
    printf("3.��Ӧ�ȸ�������(HRRN)�����㷨\n");
    printf("4.�˳�ϵͳ\n");
    printf("��ѡ��˵���(1����4):");
    while((!scanf("%d",&choic))||choic<1||choic>4)
    {
        getchar();
        printf("\n�������!!!!!!����������\n");

    }
    return choic;
}
void input() // ������ҵ���ƿ麯��
{
    int i;
    printf("��������ҵ����(2��24):");
    while(!scanf("%d",&num)||num<2||num>24)
    {
        getchar();
        printf("�������------->����������\n");
        printf("\n");
        printf("��������ҵ����(2��24):");
    }

    printf("\n");
    for(i=0;i<num;i++){
        printf("\t��%d����ҵ��:",i+1);
        scanf("%s",&jcb[i].name);
        printf("\t��������ҵ�ύʱ��:");
        scanf("%f",&jcb[i].arrivetime);
        printf("\t��������ҵ����ʱ��:");
        scanf("%f",&jcb[i].runtime);
        printf("\n");
    }
}


void quit()
{
    printf("ллʹ�ø�ϵͳ!\n");
    exit(0);
}

void output()
{
    float numT=0,numW=0,avgT=0,avgW=0;
    printf("-----------------------------------------------------------------------\n");
    printf(" ��ҵ��  �ύʱ��  ����ʱ��  ��ʼʱ��  ���ʱ��  ��תʱ��  ��Ȩ��תʱ��\n");
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
    printf("ƽ����ҵ��תʱ�䣺%.2f\n",avgT);
    printf("\n");
    printf("ƽ����Ȩ��ҵ��תʱ�䣺%.2f\n",avgW);
    printf("\n");
}
void sort()
{
    int i,j;
    for(j=0;j<num;j++)/*ð������*/
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
        if(k==0)/*���е�һ����ҵ*/
        {
            jcb[k].run=jcb[k].arrivetime;
            jcb[k].finish=jcb[k].arrivetime+jcb[k].runtime;
        }
        else
        {
            if(jcb[k].arrivetime>=jcb[k-1].finish)/*��ǰ��ҵ�Ѿ���������һ����ҵ��û�е�����߸պõ���*/
            {
                jcb[k].run=jcb[k].arrivetime;
                jcb[k].finish=jcb[k].arrivetime+jcb[k].runtime;
            }
            else/*��ǰ��ҵδ��ɣ���һ����ҵ�ѵ���*/
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
void fcfs()/*�����ȷ���*/
{
    sort();
    running();
    output();/*�����ҵ���ȱ�*/
}
void sjf()/*����ҵ����*/
{
    int next;
    float min;/*��ҵ���е���Сʱ��*/
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
            if(jcb[n].arrivetime<=jcb[m].finish)//�ж�ÿ����ҵ���֮�����ж�����ҵ����
                i++;
        }
        min=jcb[m+1].runtime;
        next=m+1;
        for(k=m+1;k<i;k++)//�ҳ���������ҵ������ʱ����С����ҵ
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
void hrrf()/*�����Ӧ������*/
{
    int flag;
    float max;//������Ӧ��
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
        max=(jcb[m].finish-jcb[m+1].arrivetime)/jcb[m+1].runtime;//��Ӧ��
        flag=m+1;
        for(k=m+1;k<i;k++)
        {
            if(max<=(jcb[k].finish-jcb[k+1].arrivetime)/jcb[k+1].runtime)//��Ӧ�ȴ����ִ��
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