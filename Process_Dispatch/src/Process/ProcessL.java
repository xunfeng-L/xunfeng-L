package Process;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class ProcessL {
    public void arCPU(ArrayList<PCB> pcbArrayList){

        Processsort processSort = new Processsort();//创建对象
        ArrayList<PCB> sortProcessList = processSort.ProcessSort(pcbArrayList);//根据优先级数排序后的进程集合
        System.out.println("          就绪进程               ");//遍历排序后的进程集合
        System.out.println("进程名      优先级     需要运行时间");
        for (int i = 0; i < sortProcessList.size(); i++) {
            String name = sortProcessList.get(i).getName();//进程名
            int priority = sortProcessList.get(i).getPriority();//优先级
            int serverTime = sortProcessList.get(i).getServeTime();//运行时间
            System.out.println(  name + "            " +priority + "           " + serverTime);
        }



        System.out.println("          运行进程          ");
        CPU cpu = new CPU();
        for (PCB pcb : sortProcessList) {
            //进程第一次进入CPU
            PCB pcb2 = cpu.Cpu(pcb);
            //进程剩余运行时间
            int serverTime = pcb2.getServeTime();
            sortProcessList.remove(pcb2);
            if (serverTime > 0) {                //若所需要的CPU时间大于0（即进程未完成）
                sortProcessList.add(pcb2);       //再次添加进进程表
            }



            if (sortProcessList.size() > 0) {         //若进程表中仍然有进程
                arCPU(sortProcessList);
            }else {
                System.out.println("进程调度结束，程序停止");
            }
        }

    }
}
