#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Box
{
    string ID;                                       //��ҵ��
    double begin_time;                               //�ύʱ��
    double rtime;                                    //�Ѿ�����ʱ��
    double turnaround_time;                          //��תʱ��
    double cpu_service_time;                         //ռ��CPU��ʱ��
    double io_time;                                  //����I/O��ʱ��
    double finish_time;                              //���ʱ��
    double Wturnaround_time;                         //��Ȩ��תʱ��
    Box& operator = (const Box& p2)                 //���� = ���������������
    {
        this->begin_time = p2.begin_time;
        this->rtime = p2.rtime;
        this->finish_time = p2.finish_time;
        this->cpu_service_time = p2.cpu_service_time;
        this->io_time = p2.io_time;
        this->ID = p2.ID;
        this->turnaround_time = p2.turnaround_time;
        this->Wturnaround_time = p2.Wturnaround_time;
        return *this;
    }
};

typedef struct
{
    Box data[100];

} JCB;

const double CPU = 10.0;
const double index = 1.0;
JCB jcb, jcb_1;
int n, number;

void init()                                                        //��ʼ����ҵ��
{
    cout << "��������ҵ��Ŀ:";
    cin >> n;
    number = n;
    for (int i = 0; i < n; i++)
    {
        cout << "JID:";
        cin >> jcb.data[i].ID;
        cout << jcb.data[i].ID << "�ύʱ��:";
        cin >> jcb.data[i].begin_time;
        cout << jcb.data[i].ID << "����cpuʱ��:";
        cin >> jcb.data[i].cpu_service_time;
        cout << jcb.data[i].ID << "����I/Oʱ��:";
        cin >> jcb.data[i].io_time;
        jcb.data[i].rtime = 0;
    }
    for (int i = 0; i < n - 1; i++)                                    //�����ύʱ���ǰ��������
    {
        for (int j = i + 1; j < n; j++)
        {
            if (jcb.data[i].begin_time > jcb.data[j].begin_time)
                swap(jcb.data[i], jcb.data[j]);
        }
    }
    for (int i = 0; i < n - 1; i++)                        //�ύʱ����ͬ�����С����ǰ
    {
        for (int j = i + 1; j < n; j++)
        {
            if (jcb.data[i].begin_time == jcb.data[j].begin_time && jcb.data[i].ID > jcb.data[j].ID)
                swap(jcb.data[i], jcb.data[j]);
        }
    }
}

void FCFS()                                                //�����ȷ���
{
    int j = 0;
    double running = CPU;
    double bt = jcb.data[0].begin_time;
    double gtt = 0;
    double gwtt = 0;
    double real_begin;
    double record = jcb.data[j].begin_time;
    int num = n - 1;
    cout << "JID     " << "�ύʱ��  " << "��תʱ��  " << "���ʱ��  " << "��Ȩ��תʱ��" << endl;
    while (1)
    {
        if (jcb.data[j].cpu_service_time > CPU)
        {
            cout << "over running range!!!" << endl;
            exit(0);
        }
        jcb.data[j].rtime += index;
        record += index;
        if (running >= 0)
        {
            if (jcb.data[j].rtime >= jcb.data[j].cpu_service_time)
            {
                real_begin = bt;
                jcb.data[j].finish_time = record + jcb.data[j].io_time;
                jcb.data[j].turnaround_time = jcb.data[j].finish_time - jcb.data[j].begin_time;
                jcb.data[j].Wturnaround_time = jcb.data[j].turnaround_time / jcb.data[j].rtime;
                cout << jcb.data[j].ID << "         "
                     << jcb.data[j].begin_time << "          " << jcb.data[j].turnaround_time
                     << "         " << jcb.data[j].finish_time << "          "
                     << jcb.data[j].Wturnaround_time << endl;
                n--;
                running -= jcb.data[j].cpu_service_time;
                bt = record;
                gtt += jcb.data[j].turnaround_time;
                gwtt += jcb.data[j].Wturnaround_time;
            }
            else
            {
                num++;
                swap(jcb.data[num], jcb.data[j]);
            }
        }
        else
        {
            running += jcb.data[j].cpu_service_time;
            num++;
            swap(jcb.data[num], jcb.data[j]);
        }
        if (n == 0)
            break;
        j++;
    }
    cout << " ƽ����תʱ��:" << gtt / number << endl << "ƽ����Ȩ��תʱ��:" << gwtt / number << endl;
}


int main()

{
    init();
    FCFS();
    return 0;
}