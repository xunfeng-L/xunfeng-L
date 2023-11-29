#include <stdio.h>
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))

struct jcb { // 定义作业控制块JCB
    char name[10];
    char state; //作业状态，就绪，运行，完成
    double super;  //优先级
    int atime;  //作业到达时间
    int ntime;  //作业需要的运行时间
    double Ttime;   //周转时间
    double Wtime;   //带权周转时间
    struct jcb* link;   //就绪队列链表
}*ready = NULL, *p;    //ready为就绪队列，p为正在运行的作业或新加的作业

typedef struct jcb JCB;

double finTime; //记录某作业完成时间
int nowtime = 0;
double totalTtime = 0, totalWtime = 0; //总周转时间，总带权周转时间
int length = 0; //总作业数
int cho;    //选择采用何种算法

void FCFS()  //建立先来先服务函数
{
    JCB *first, *second;
    int insert = 0;
    if ((ready == NULL) || ((p->atime) < (ready->atime))) //作业先来,插入队首
    {
        p->link = ready;
        ready = p;
    }
    else if (p->atime == ready->atime && p->ntime < ready->ntime)    //同时到达，设为短作业优先
    {
        p->link = ready;
        ready = p;
    }
    else // 作业比较到达时间,插入适当的位置中
    {
        first = ready;
        second = first->link;
        while (second != NULL)
        {
            if ((p->atime) < (second->atime)) //若插入作业比当前作业到达时间前
            {                               //插入到当前作业前面
                p->link = second;
                first->link = p;
                second = NULL;
                insert = 1;
            }
            else // 插入作业到达的时间最晚,则插入到队尾
            {
                first = first->link;
                second = second->link;
            }
        }
        if (insert == 0) first->link = p;
    }
}

void sort() //按照响应比对链表结点进行冒泡排序
{
    JCB *head;
    head = getpch(JCB);
    head->link = ready;
    JCB *q, *prep, *temp, *tail;
    tail = NULL;
    while (head->link != tail)
    {
        prep = head;
        q = head->link;
        while (q->link != tail)
        {
            if (q->super < q->link->super)
            {
                temp = q->link;
                prep->link = q->link;
                q->link = q->link->link;
                prep->link->link = q;
                q = temp;
            }
            //结点后移
            q = q->link;
            prep = prep->link;
        }
        tail = q;
    }
    ready = head->link;
    head->link = NULL;
    free(head);
}

void HRRN() //建立响应比高者优先函数
{
    if (nowtime == 0)
        FCFS(); //还没有作业读入内存时，用先来先服务算法
    else
        sort(); //已经有作业读入内存后，按照响应比排序
}

void input() // 建立进程控制块函数
{
    int i, num;
    printf("\n 请输入需要添加的作业个数：");
    scanf("%d", &num);
    length += num;
    for (i = 0; i < num; i++)
    {
        //printf("\n 作业号No.%d:\n", i + 1);
        p = getpch(JCB);    //分配空间
        printf("\n 输入作业名:");
        scanf("%s", p->name);
        printf("\n请输入作业到达时间:");
        scanf("%d", &p->atime);
        printf("\n 输入作业需要的运行时间:");
        scanf("%d", &p->ntime);
        printf("\n");
        p->super = (nowtime - p->atime) / p->ntime + 1;
        p->state = 'w';
        p->link = NULL;
        if (cho == 1)
            FCFS(); // 调用先来先服务函数
        else
            HRRN(); //调用高响应比优先函数
    }
}

int space() //计算剩余作业数
{
    int len = 0;
    JCB* pr = ready;
    while (pr != NULL)
    {
        len++;
        pr = pr->link;
    }
    return(len);
}

void disp(JCB * pr) //建立进程显示函数,用于显示就绪进程
{
    if (cho == 0)
    {
        printf("\n作业名   到达时间   状态   需要的时间\n");
        printf(" %s", pr->name);
        printf("         %d", pr->atime);
        printf("         %c", pr->state);
        printf("        %d", pr->ntime);
        printf("\n");
    }
    else
    {
        printf("\n作业名   到达时间   状态   需要的时间   等待时间   响应比\n");
        printf(" %s", pr->name);
        printf("         %d", pr->atime);
        printf("         %c", pr->state);
        printf("        %d", pr->ntime);
        printf("           %d", nowtime - pr->atime);
        printf("        %.2f", pr->super);
        printf("\n");
    }
}

void destroy() //建立作业撤消函数(作业运行结束,撤消作业)
{
    printf("\n 作业 [%s] 已完成.\n", p->name);
    free(p);
}

void running() // 运行内存中的作业
{
    finTime = nowtime; //完成时刻
    p->Ttime = finTime - p->atime; //周转时间
    p->Wtime = p->Ttime / p->ntime; //带权周转时间
    printf("\n作业名  提交时间  需要时间  完成时间  状态  周转时间  带权周转时间\n");
    printf("   %s       %d        %d        %.2f      %c     %.2f      %.2f\n", p->name, p->atime, p->ntime,
           finTime, p->state, p->Ttime, p->Wtime);

    totalTtime += p->Ttime;
    totalWtime += p->Wtime;
}

void check() // 建立作业查看函数
{
    JCB *pr;
    printf("\n **** 当前正在运行的作业是:%s", p->name); //显示当前运行的作业
    running();
    pr = ready;
    if (cho == 1)    //如果用高响应比优先算法，
    {               //则有作业完成时要更新响应比且重新排序就绪队列
        while (pr != NULL)
        {
            if (nowtime < pr->atime)
            {
                pr = pr->link;
                continue;
            }
            pr->super = ((nowtime - pr->atime) * 1.0) / pr->ntime + 1; //更新响应比
            pr = pr->link;
        }
        HRRN(); //重新排序
        pr = ready;
    }
    printf("\n ****当前就绪队列状态为:\n"); //显示就绪队列状态
    while (pr != NULL)
    {
        if (nowtime < pr->atime)
        {
            pr = pr->link;
            continue;
        }
        disp(pr);
        pr = pr->link;
    }
    destroy();
}

int main() //主函数
{
    int len;
    while (1)
    {
        printf("\t\t\t************************作业调度算法**************************\n\t\t\t" );
        printf("\t\t\t先来先服务算法:0\n\t\t\t    \t\t\t 高响应比优先算法:1\n");
        printf("\t\t\t********************************************************\n\t\t\t");
        printf("\t\t\t请输入数字选择对应的调度算法: ");
        scanf("%d", &cho);
        printf("\n\t---------------------------------------------------------------\n");
        if (cho == 0 || cho == 1)
            break;
        else
        {
            printf("\t\t\t输入错误，请重新输入!\n\n");
            continue;
        }
    }
    input();
    len = space();
    finTime = ready->atime;
    while ((len != 0) && (ready != NULL))
    {
        getchar();
        p = ready;
        nowtime = p->ntime + finTime;
        printf("\n\n现在的时间是:%d \n", nowtime);
        ready = p->link;
        p->link = NULL;
        p->state = 'R';
        check();
    }
    if (cho == 0)
    {
        printf("\n 所以作业已经完成,先来先服务算法模拟结束\n\n");
    }
    else
    {
        printf("\n 所以作业已经完成,高响应比优先算法模拟结束\n\n");
    }
    printf("本组作业的平均周转时间为：%.2f\n", totalTtime / length);
    printf("本组作业的平均带权周转时间为：%.2f\n", totalWtime / length);
    getchar();
    return 0;
}