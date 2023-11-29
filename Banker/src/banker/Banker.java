package banker;

import java.util.Scanner;
public class Banker {
    static int  maximun=100;
    int M=maximun;
    int N=maximun;
    String Name[] = new String[maximun];           //资源名
    int Max[][] = new int[maximun][maximun];       //最大需求矩阵
    int Allocation[][] = new int[maximun][maximun];//系统已分配矩阵
    int Need[][] = new int[maximun][maximun];      //需要资源矩阵
    int Available[] = new int[maximun];            //可用资源向量
    int Request[] = new int[maximun];              //请求资源向量
    int Work[] = new int[maximun];                 //工作向量，存放系统可提供资源量




    Scanner sc = new Scanner(System.in);

    //初始化各类数据
    public void init() {

        int i, j, m, n;
        int number;
        boolean flag;
        String name;//输入资源名称
        int temp[] = new int[maximun];//统计已分配资源
        //输入系统资源数目及各资源初始个数
        System.out.print("系统拥有资源种类个数为:");
        n = sc.nextInt();
        N = n;
        for (i = 0; i <n; i++) {
            sc.nextLine();//清空缓冲区否则可能导致无法输入报出异常
            System.out.println("第" + i + "个资源的名称为:");
            name = sc.nextLine();
            Name[i] = name;
            System.out.println("系统拥有资源" + name + "的个数为:");
            number = sc.nextInt();
            Available[i] = number;
        }
        //输入进程数及各进程的最大需求矩阵
        System.out.println("请输入进程数:");
        m = sc.nextInt();
        M = m;
        System.out.println("请输入各进程的最大需求矩阵:");
        do {
            flag = false;
            for (i = 0; i < M; i++) {
                for (j = 0; j < N; j++) {
                    Max[i][j] = sc.nextInt();
                    if (Max[i][j] > Available[j])   //判断需求资源量是否超过系统拥有的资源量
                    {
                        flag = true;
                    }
                }
            }
            if (flag) {
                System.out.println("Max>系统资源最大量，输入失败！");
            }
        } while (flag);

        //输入各进程已经分配的资源量，并求得还需要的资源量
        do {
            flag = false;
            System.out.println("请输入各进程的[Allocation]:");
            for (i = 0; i < M; i++) {
                for (j = 0; j < N; j++) {
                    Allocation[i][j] = sc.nextInt();
                    if (Allocation[i][j] > Max[i][j]) {
                        flag = true;
                    }
                    Need[i][j] = Max[i][j] - Allocation[i][j];   //算出Need矩阵
                    temp[j] += Allocation[i][j];                 //统计已经分配给进程的资源数目
                }
            }
            if (flag) {
                System.out.println("分配的资源大于最大量，请重新输入!");
            }
        } while (flag);

        //求得系统中现有的可利用的资源量
        for (j = 0; j < N; j++) {
            Available[j] = Available[j] - temp[j];
        }
    }

    //显示资源分配矩阵
    public void showdata() {
        int i, j;

        System.out.println("*************************************************************");
        System.out.println("系统目前可用的资源[Available]:");
        for (i = 0; i < N; i++) {
            System.out.print(Name[i] + "  ");
        }
        System.out.println();
        for (j = 0; j < N; j++) {
            System.out.print(Available[j] + "  ");
        }
        System.out.println();
        System.out.println("系统当前的资源分配情况如下：");
        System.out.println("         Max   	    Allocation      Need");
        System.out.print("进程名     ");
        //输出与进程名同行的资源名，Max、Allocation、Need下分别对应
        for (j = 0; j < 3; j++) {
            for (i = 0; i < N; i++) {
                System.out.print(Name[i] + "  ");
            }
            System.out.print("     ");
        }
        System.out.println();
        //输出每个进程的Max、Allocation、Need
        for (i = 0; i < M; i++) {
            System.out.print("P" + i + "    ");
            for (j = 0; j < N; j++) {
                System.out.print(Max[i][j] + "  ");
            }
            System.out.print("     ");
            for (j = 0; j < N; j++) {
                System.out.print(Allocation[i][j] + "  ");
            }
            System.out.print("     ");
            for (j = 0; j < N; j++) {
                System.out.print(Need[i][j] + "  ");
            }
            System.out.println();
        }
    }

    //尝试分配资源
    public void set(int i) {
        for (int j = 0; j < N; j++) {
            Available[j] = Available[j] - Request[j];
            Allocation[i][j] = Allocation[i][j] + Request[j];
            Need[i][j] = Need[i][j] - Request[j];
        }
    }

    //试探性分配资源作废，与test操作相反
    public int reset(int i) {
        for (int j = 0; j < N; j++) {
            Available[j] = Available[j] + Request[j];
            Allocation[i][j] = Allocation[i][j] - Request[j];
            Need[i][j] = Need[i][j] + Request[j];
        }
        return 1;
    }

    //安全性算法
    public int Security() {
        boolean[] Finish = new boolean[M];
        for (int i = 0; i <M; i++) {
            Finish[i]=false;
        }
        int count = 0;//完成进程数
        int circle = 0;//循环圈数
        int[] SecurityList = new int[M];//安全序列
        for (int i = 0; i < M; i++) {     //设置工作向量
            Work[i] = Available[i];
        }
        boolean flag = true;
        while (count < M) {
            if (flag) {
                System.out.println("R" +
                        "进程  " + "   Work  " + "   Allocation " + "    Need  " + "     Work+Allocation ");
                flag = false;
            }
            for (int i = 0; i < M; i++) {

                if (!Finish[i]&&Need[i][0]<=Work[0]&&Need[i][1]<=Work[1]&&Need[i][2]<=Work[2]) {//判断条件

                    System.out.print("P" + i + "  ");
                    for (int k = 0; k < N; k++) {
                        System.out.print(Work[k] + "  ");
                    }
                    System.out.print("|  ");
                    for (int j = 0; j < N; j++) {
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = true;//当当前进程能满足时
                    SecurityList[count] = i;//设置当前序列排号

                    count++;//满足进程数加1
                    for (int j = 0; j < N; j++) {
                        System.out.print(Allocation[i][j] + "  ");
                    }
                    System.out.print("|  ");
                    for (int j = 0; j < N; j++) {
                        System.out.print(Need[i][j] + "  ");
                    }
                    System.out.print("|  ");
                    for (int j = 0; j < N; j++) {
                        System.out.print(Work[j] + "  ");
                    }
                    System.out.println();
                }

            }
            circle++;//循环圈数加1

            if (count == M) {//判断是否满足所有进程需要
                System.out.print("此时存在一个安全序列：");
                for (int i = 0; i < M; i++) {//输出安全序列
                    System.out.print("P" + SecurityList[i] + " ");
                }
                System.out.println("故当前可分配！");

                break;//跳出循环
            }
            if (count < circle) {//判断完成进程数是否小于循环圈数
                System.out.println("当前系统处于不安全状态，故不存在安全序列。");
                break;//跳出循环
            }
        }
    return count;
    }

    //银行家算法处理申请资源
    public void bank() {
        boolean Flag=true;
        int i,j;
        System.out.println("进程号(0~"+(M-1)+"):");
        i=sc.nextInt();
        System.out.println("输入进程P"+i+"要申请的资源详情:");
        for(j=0;j<N;j++)
        {
            System.out.print(Name[j]+":");
            Request[j]=sc.nextInt();//输入需要申请的资源
        }

        //判断银行家算法的前两条件是否成立
        for(j=0;j<N;j++)
        {
            if(Request[j]>Need[i][j])
            {
                System.out.print("进程P"+i+"申请的资源大于它需要的的资源数");
                Flag=false;
                break;
            }
            else
            {
                if(Request[j]>Available[j])
                {
                    System.out.print("进程"+i+"申请的资源大于系统现在可利用的资源");
                    System.out.println();
                    Flag=false;
                    break;
                }
            }
        }


        if(Flag)
        {
            set(i);
            showdata();
            if(Security()!=M){
                reset(i);
                showdata();
            }
        }
    }

    //主函数
    public static void main(String[] args) {
        Banker b=new Banker();
        Scanner sc=new Scanner(System.in);
        String choice;
        System.out.println("                       银行家算法                          ");
        b.init();
        b.showdata();
        b.Security();

        do
        {
            System.out.println("                     按R:请求资源 ");
            System.out.println("                     按E:退出       ");
            System.out.print("请选择：");
            choice=sc.nextLine();
            switch(choice)
            {
                case "r":
                case "R":
                    b.bank();
                    break;
                case "e":
                case "E":
                    System.exit(0);//System.exit(0)是正常退出程序，System.exit(1)表示非正常退出程序。
                default:
                    System.out.println("请正确选择！");
                    break;
            }
        }while(!choice.equals(""));
    }
}
