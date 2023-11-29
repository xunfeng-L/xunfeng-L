package Process;

import java.util.ArrayList;

public class ProcessL {
    public void arCPU(ArrayList<PCB> pcbArrayList){


        System.out.println("          就绪进程               ");
        System.out.println("进程名      需要运行时间");
        for (int i = 0; i < pcbArrayList.size(); i++) {
            String name = pcbArrayList.get(i).getName();//进程名
            int serverTime = pcbArrayList.get(i).getServeTime();//运行时间
            System.out.println(  name + "            " + serverTime);
        }
        System.out.println("          运行进程          ");
        CPU cpu = new CPU();
        for (PCB pcb : pcbArrayList) {
            //进程第一次进入CPU
            PCB pcb2 = cpu.Cpu(pcb);
            //进程剩余运行时间
            int serverTime = pcb2.getServeTime();
            pcbArrayList.remove(pcb2);
            if (serverTime > 0) {                //若所需要的CPU时间大于0（即进程未完成）
                pcbArrayList.add(pcb2);       //再次添加进进程表
            }
            if (pcbArrayList.size() > 0) {         //若进程表中仍然有进程
                arCPU(pcbArrayList);
            }else {
                System.out.println("进程调度结束，程序停止");
            }
        }
    }

}
