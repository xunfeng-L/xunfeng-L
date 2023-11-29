package Process;

import java.util.ArrayList;
import java.util.Scanner;

public class Test {

    public static void main(String[] args) {
        Scanner scanner1 = new Scanner(System.in);
        System.out.println("请输入进程数：");
        int processNum = scanner1.nextInt();//processNum为进程数

        Scanner scanner2 = new Scanner(System.in);
        System.out.println("请输入进程名");
        String names = scanner2.nextLine();
        String[] nameList = names.split(" ");//存储进程名字分割后的数组

        //随机生成进程所需的时间
        int[] RunTimeList = new int[processNum];//每个进程需要运行的时间数组
        for (int i = 0; i <processNum; i++){
            RunTimeList[i] = (int)(Math.random()*(20-1+1)+1);
        }    //赋值过程

        for (int i = 0; i <processNum; i++) {
            System.out.println("第"+(i+1)+"进程的所需的CPU时间为(自动生成，范围为1-20)："+RunTimeList[i]);
        }   //打印过程

        ArrayList<PCB> pcbArrayList = new ArrayList<PCB>();//存储所有已就绪进程对象的集合
        //循环初始化进程对象
        for (int i = 0; i < processNum; i++) {
            //进程名字
            String name = nameList[i];
            int serverTime = RunTimeList[i];
            PCB pcb = new PCB();
            pcb.setName(name);
            pcb.setServeTime(serverTime);
            //把设置完毕的进程存入存储就绪进程的集合
            pcbArrayList.add(pcb);
        }
        ProcessL processL = new ProcessL();
        processL.arCPU(pcbArrayList);

    }
}
