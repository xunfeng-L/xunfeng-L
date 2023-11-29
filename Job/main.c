#include <stdio.h>
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))

struct jcb { // ������ҵ���ƿ�JCB
    char name[10];
    char state; //��ҵ״̬�����������У����
    double super;  //���ȼ�
    int atime;  //��ҵ����ʱ��
    int ntime;  //��ҵ��Ҫ������ʱ��
    double Ttime;   //��תʱ��
    double Wtime;   //��Ȩ��תʱ��
    struct jcb* link;   //������������
}*ready = NULL, *p;    //readyΪ�������У�pΪ�������е���ҵ���¼ӵ���ҵ

typedef struct jcb JCB;

double finTime; //��¼ĳ��ҵ���ʱ��
int nowtime = 0;
double totalTtime = 0, totalWtime = 0; //����תʱ�䣬�ܴ�Ȩ��תʱ��
int length = 0; //����ҵ��
int cho;    //ѡ����ú����㷨

void FCFS()  //���������ȷ�����
{
    JCB *first, *second;
    int insert = 0;
    if ((ready == NULL) || ((p->atime) < (ready->atime))) //��ҵ����,�������
    {
        p->link = ready;
        ready = p;
    }
    else if (p->atime == ready->atime && p->ntime < ready->ntime)    //ͬʱ�����Ϊ����ҵ����
    {
        p->link = ready;
        ready = p;
    }
    else // ��ҵ�Ƚϵ���ʱ��,�����ʵ���λ����
    {
        first = ready;
        second = first->link;
        while (second != NULL)
        {
            if ((p->atime) < (second->atime)) //��������ҵ�ȵ�ǰ��ҵ����ʱ��ǰ
            {                               //���뵽��ǰ��ҵǰ��
                p->link = second;
                first->link = p;
                second = NULL;
                insert = 1;
            }
            else // ������ҵ�����ʱ������,����뵽��β
            {
                first = first->link;
                second = second->link;
            }
        }
        if (insert == 0) first->link = p;
    }
}

void sort() //������Ӧ�ȶ����������ð������
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
            //������
            q = q->link;
            prep = prep->link;
        }
        tail = q;
    }
    ready = head->link;
    head->link = NULL;
    free(head);
}

void HRRN() //������Ӧ�ȸ������Ⱥ���
{
    if (nowtime == 0)
        FCFS(); //��û����ҵ�����ڴ�ʱ���������ȷ����㷨
    else
        sort(); //�Ѿ�����ҵ�����ڴ�󣬰�����Ӧ������
}

void input() // �������̿��ƿ麯��
{
    int i, num;
    printf("\n ��������Ҫ��ӵ���ҵ������");
    scanf("%d", &num);
    length += num;
    for (i = 0; i < num; i++)
    {
        //printf("\n ��ҵ��No.%d:\n", i + 1);
        p = getpch(JCB);    //����ռ�
        printf("\n ������ҵ��:");
        scanf("%s", p->name);
        printf("\n��������ҵ����ʱ��:");
        scanf("%d", &p->atime);
        printf("\n ������ҵ��Ҫ������ʱ��:");
        scanf("%d", &p->ntime);
        printf("\n");
        p->super = (nowtime - p->atime) / p->ntime + 1;
        p->state = 'w';
        p->link = NULL;
        if (cho == 1)
            FCFS(); // ���������ȷ�����
        else
            HRRN(); //���ø���Ӧ�����Ⱥ���
    }
}

int space() //����ʣ����ҵ��
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

void disp(JCB * pr) //����������ʾ����,������ʾ��������
{
    if (cho == 0)
    {
        printf("\n��ҵ��   ����ʱ��   ״̬   ��Ҫ��ʱ��\n");
        printf(" %s", pr->name);
        printf("         %d", pr->atime);
        printf("         %c", pr->state);
        printf("        %d", pr->ntime);
        printf("\n");
    }
    else
    {
        printf("\n��ҵ��   ����ʱ��   ״̬   ��Ҫ��ʱ��   �ȴ�ʱ��   ��Ӧ��\n");
        printf(" %s", pr->name);
        printf("         %d", pr->atime);
        printf("         %c", pr->state);
        printf("        %d", pr->ntime);
        printf("           %d", nowtime - pr->atime);
        printf("        %.2f", pr->super);
        printf("\n");
    }
}

void destroy() //������ҵ��������(��ҵ���н���,������ҵ)
{
    printf("\n ��ҵ [%s] �����.\n", p->name);
    free(p);
}

void running() // �����ڴ��е���ҵ
{
    finTime = nowtime; //���ʱ��
    p->Ttime = finTime - p->atime; //��תʱ��
    p->Wtime = p->Ttime / p->ntime; //��Ȩ��תʱ��
    printf("\n��ҵ��  �ύʱ��  ��Ҫʱ��  ���ʱ��  ״̬  ��תʱ��  ��Ȩ��תʱ��\n");
    printf("   %s       %d        %d        %.2f      %c     %.2f      %.2f\n", p->name, p->atime, p->ntime,
           finTime, p->state, p->Ttime, p->Wtime);

    totalTtime += p->Ttime;
    totalWtime += p->Wtime;
}

void check() // ������ҵ�鿴����
{
    JCB *pr;
    printf("\n **** ��ǰ�������е���ҵ��:%s", p->name); //��ʾ��ǰ���е���ҵ
    running();
    pr = ready;
    if (cho == 1)    //����ø���Ӧ�������㷨��
    {               //������ҵ���ʱҪ������Ӧ�������������������
        while (pr != NULL)
        {
            if (nowtime < pr->atime)
            {
                pr = pr->link;
                continue;
            }
            pr->super = ((nowtime - pr->atime) * 1.0) / pr->ntime + 1; //������Ӧ��
            pr = pr->link;
        }
        HRRN(); //��������
        pr = ready;
    }
    printf("\n ****��ǰ��������״̬Ϊ:\n"); //��ʾ��������״̬
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

int main() //������
{
    int len;
    while (1)
    {
        printf("\t\t\t************************��ҵ�����㷨**************************\n\t\t\t" );
        printf("\t\t\t�����ȷ����㷨:0\n\t\t\t    \t\t\t ����Ӧ�������㷨:1\n");
        printf("\t\t\t********************************************************\n\t\t\t");
        printf("\t\t\t����������ѡ���Ӧ�ĵ����㷨: ");
        scanf("%d", &cho);
        printf("\n\t---------------------------------------------------------------\n");
        if (cho == 0 || cho == 1)
            break;
        else
        {
            printf("\t\t\t�����������������!\n\n");
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
        printf("\n\n���ڵ�ʱ����:%d \n", nowtime);
        ready = p->link;
        p->link = NULL;
        p->state = 'R';
        check();
    }
    if (cho == 0)
    {
        printf("\n ������ҵ�Ѿ����,�����ȷ����㷨ģ�����\n\n");
    }
    else
    {
        printf("\n ������ҵ�Ѿ����,����Ӧ�������㷨ģ�����\n\n");
    }
    printf("������ҵ��ƽ����תʱ��Ϊ��%.2f\n", totalTtime / length);
    printf("������ҵ��ƽ����Ȩ��תʱ��Ϊ��%.2f\n", totalWtime / length);
    getchar();
    return 0;
}