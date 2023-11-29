package Process;         //定义一个CPU类，

public class CPU {
    
    static int  timeSlice = (int)(Math.random()*(5-1+1)+1) ;//CPU一个时间片时长
    static int currentTime = 0; //记录进程的进入时间，每当运行一个进程，需要相应增加

    public PCB Cpu(PCB pcb){
        pcb.setArriveTime(currentTime);   //初始化进程到达时间
        pcb.setBeginTime(currentTime);    //初始化进程开始时间
        int serverTime=pcb.getServeTime();      //取出进程的服务时间（为随机数生成）
        if(serverTime<=timeSlice){
            pcb.setFinishTime(currentTime+serverTime);    //得出进程结束时间
            currentTime+=serverTime;                      //每当运行一个进程，该数字需要相应增加
            pcb.setRoundTime(serverTime);                        //得出周转时间
            pcb.setServeTime(0);                                  //服务时间置0
            System.out.println("时间片（自动生成,范围为1-5的整数）:" + timeSlice + "" + "; 本次处理的进程：" + pcb.getName() +"; 进程进入CPU时刻："
                    + pcb.getArriveTime() + "; 进程需运行的时间：" + serverTime + "; 进程结束时刻：" + pcb.getFinishTime());
        }          //若服务时间小于等于一个时间片
        else{
            int serverTimeResidue = serverTime - timeSlice;    //得出剩余需要的服务时间
            pcb.setServeTime(serverTimeResidue);             //把这个剩余的服务时间再赋给进程所需的服务时间
            pcb.setPriority(pcb.getPriority() - 3);          //并且进程优先级减3
            currentTime += timeSlice;                  //时间延后
            System.out.println("时间片" + timeSlice + "" + "; 本次处理的进程：" + pcb.getName() +"; 进程进入CPU时刻："
                    + pcb.getArriveTime() + "; 进程还需运行的时间：" + serverTimeResidue + "; 进程优先级减去3");
        }                               //进程所需服务时间大于一个时间片
        return pcb;
    }
}
