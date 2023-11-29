package job;


import java.util.Scanner;
import java.io.File;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.Comparator;

public class Bp{

    private int numberOfTracks;//批处理系统道数
    private Job[] jobs;//作业放入的数组
    private int jobCnt;//作业总数
    private int memoryJobCnt;//内存中作业数目
    private int currentHour;//当前时间的小时
    private int currentMinute;//当前时间的分钟
    private String jobAlgorithmOption;//作业调度算法选择标记
    private String processAlgorithmOption;//进程调度算法选择标记


    public void setNumberOfTracks(int numberOfTracks){
        this.numberOfTracks = numberOfTracks;
    }
    public int getNumberOfTracks(){
        return this.numberOfTracks;
    }

    public void setJobs(Job[] jobs){
        this.jobs = jobs;
    }
    public Job[] getJobs(){
        return this.jobs;
    }

    public void setJobCnt(int jobCnt){
        this.jobCnt = jobCnt;
    }
    public int getJobCnt(){
        return this.jobCnt;
    }

    public void setMemoryJobCnt(int memoryJobCnt){
        this.memoryJobCnt = memoryJobCnt;
    }
    public int getMemoryJobCnt(){
        return this.memoryJobCnt;
    }

    public void setCurrentHour(int currentHour){
        this.currentHour = currentHour;
    }
    public int getCurrentHour(){
        return this.currentHour;
    }

    public void setCurrentMinute(int currentMinute){
        this.currentMinute = currentMinute;
    }
    public int getCurrentMinute(){
        return this.currentMinute;
    }

    public void setJobAlgorithmOption(String jobAlgorithmOption){
        this.jobAlgorithmOption = jobAlgorithmOption;
    }
    public String getJobAlgorithmOption(){
        return this.jobAlgorithmOption;
    }

    public void setProcessAlgorithmOption(String processAlgorithmOption){
        this.processAlgorithmOption = processAlgorithmOption ;
    }
    public String getProcessAlgorithmOption(){
        return processAlgorithmOption;
    }

    //空参构造
    public void Bp(){}

    //读入数据
    public void input(String path){
        try{
            File in = new File(path);//输入文件

            BufferedReader br = new BufferedReader(new FileReader(in));//输入流

            int jobCnt = 0;//作业数目
            String line = null;

            while((line = br.readLine()) != null){

                Job[] jobs = this.getJobs();

                jobs[jobCnt] = new Job();

                //一次读取一行，用空格进行劈开，三个值分别是作业的名称、开始时间、估计运行时间
                String[] splits = line.split(" ");
                jobs[jobCnt].setName(splits[0]);
                jobs[jobCnt].setStartTime(splits[1]);
                jobs[jobCnt].setExecuteTime(Integer.parseInt(splits[2]));

                String[] hourMinute = splits[1].split(":");
                jobs[jobCnt].setStartHour(Integer.parseInt(hourMinute[0]));
                jobs[jobCnt].setStartMinute(Integer.parseInt(hourMinute[1]));

                jobs[jobCnt].setExecuteRemainingTime(Integer.parseInt(splits[2]));

                jobs[jobCnt].setState(false);
                jobs[jobCnt].setInMemory(false);

                jobs[jobCnt].setFirstExecute(true);

                jobCnt++;//每读进来一个作业，作业数目加1

            }
            br.close();//关闭流，否则可能I/O操作失败
            this.setJobCnt(jobCnt);
            this.setCurrentHour(jobs[0].getStartHour());
            this.setCurrentMinute(jobs[0].getStartMinute());

        }catch(Exception e){
            e.printStackTrace();
        }

    }

    public void jobFCFS(){
        Job[] jobs = this.getJobs();
        int times = this.getNumberOfTracks() - this.getMemoryJobCnt();
        int tmpCnt = 0;//临时变量，累计本次调入内存的数目，最多达到times个
        int jobCnt = this.getJobCnt();
        int currentHour = this.getCurrentHour();
        int currentMinute = this.getCurrentMinute();
        int memoryJobCnt = this.getMemoryJobCnt();

        for(int i =0 ;i < jobCnt; i++){
            if(tmpCnt >= times){break;}//如果调入内存的作业数目大于了本次内存允许调用的数目，终止。若只允许调入1个，那么tmpCnt=1时候终止循环
            if((jobs[i].getStartHour() < currentHour || (jobs[i].getStartHour() == currentHour && jobs[i].getStartMinute() <= currentMinute))
                    && jobs[i].getInMemory()==false && jobs[i].getState() == false){
                jobs[i].setInMemory(true);
                memoryJobCnt++;
                tmpCnt++;
            }
        }
        this.setMemoryJobCnt(memoryJobCnt);

    }

    public void jobSJF(){
        Job[] jobs = this.getJobs();
        int times = this.getNumberOfTracks() - this.getMemoryJobCnt();
        int jobCnt = this.getJobCnt();
        int currentHour = this.getCurrentHour();
        int currentMinute = this.getCurrentMinute();
        int memoryJobCnt = this.getMemoryJobCnt();

        //暴力挑选最多times个最短作业到内存
        while(times>0){
            int minimumTime = 1000000;//假定最长时间不超过1000000
            int pos = -1;//本次要选谁去内存
            for(int i =0 ;i < jobCnt; i++){

                if((jobs[i].getStartHour() < currentHour || (jobs[i].getStartHour() == currentHour && jobs[i].getStartMinute() <= currentMinute))
                        && jobs[i].getInMemory()==false && jobs[i].getState() == false && jobs[i].getExecuteTime() < minimumTime){
                    minimumTime = jobs[i].getExecuteTime();
                    pos = i;

                }
            }
            if(pos != -1){
                jobs[pos].setInMemory(true);
                memoryJobCnt++;
            }
            times--;
        }

        this.setMemoryJobCnt(memoryJobCnt);

    }

    public void jobHRRN(){

        Job[] jobs = this.getJobs();
        int times = this.getNumberOfTracks() - this.getMemoryJobCnt();
        int jobCnt = this.getJobCnt();
        int currentHour = this.getCurrentHour();
        int currentMinute = this.getCurrentMinute();
        int memoryJobCnt = this.getMemoryJobCnt();

        //暴力挑选最多times个最高响应比作业到内存
        while(times>0){
            double responseRatio = -1.0;//最高响应比
            int pos = -1;//本次要选谁去内存
            for(int i =0 ;i < jobCnt; i++){
                int waitTime = (currentHour - jobs[i].getStartHour() - 1)*60 + 60 +currentMinute - jobs[i].getStartMinute();
                double tmpRatio = (double)waitTime/(double)jobs[i].getExecuteTime();
                if((jobs[i].getStartHour() < currentHour || (jobs[i].getStartHour() == currentHour && jobs[i].getStartMinute() <= currentMinute))
                        && jobs[i].getInMemory()==false && jobs[i].getState() == false && tmpRatio > responseRatio ){
                    responseRatio = tmpRatio;
                    pos = i;

                }
            }
            if(pos != -1){
                jobs[pos].setInMemory(true);
                memoryJobCnt++;
            }
            times--;
        }

        this.setMemoryJobCnt(memoryJobCnt);
    }


    public int processFCFS(){

        Job[] jobs = this.getJobs();
        int jobCnt = this.getJobCnt();

        //************************从内存选一个作业（准备执行）************************
        //作业已经调入内存，并且此刻内存中必定有没有执行完的作业。因为系统是串行的，必定选择一个作业执行。
        //选择以当前时间为起点最先来的作业执行
        int pos = -1;
        for(int i = 0; i < jobCnt ;i++){
            if(jobs[i].getInMemory()==true){
                pos = i;
                break;
            }
        }
        return pos;
    }

    public int processSJF(){

        Job[] jobs = this.getJobs();
        int jobCnt = this.getJobCnt();

        //************************从内存选一个作业（准备执行）************************
        //作业已经调入内存，并且此刻内存中必定有没有执行完的作业。因为系统是串行的，必定选择一个作业执行。
        //选择以当前时间为起点运行时间最短的作业执行

        int minimumTime = 1000000;//假定最长作业时间不会超过1000000
        int pos = -1;//最短作业对应的数组下标
        for(int i = 0; i < jobCnt ;i++){
            if(jobs[i].getInMemory()==true && jobs[i].getExecuteRemainingTime() < minimumTime){
                minimumTime = jobs[i].getExecuteRemainingTime();
                pos = i;
            }
        }
        return pos;
    }

    public int processHRRN(){

        Job[] jobs = this.getJobs();
        int jobCnt = this.getJobCnt();
        int currentHour = this.getCurrentHour();
        int currentMinute = this.getCurrentMinute();

        //************************从内存选一个作业（准备执行）************************
        //作业已经调入内存，并且此刻内存中必定有没有执行完的作业。因为系统是串行的，必定选择一个作业执行。
        //选择以当前时间为起点最高响应比的作业执行

        double responseRatio = -1.0;
        int pos = -1;//最短作业对应的数组下标
        for(int i = 0; i < jobCnt ;i++){
            int waitTime = (currentHour - jobs[i].getStartHour() - 1)*60 + 60 +currentMinute - jobs[i].getStartMinute();
            double tmpRatio = (double)waitTime/(double)jobs[i].getExecuteTime();
            if(jobs[i].getInMemory()==true && tmpRatio>responseRatio){
                responseRatio = tmpRatio;
                pos = i;
            }
        }
        return pos;
    }

    public void exe(int pos){

        Job[] jobs = this.getJobs();
        int memoryJobCnt = this.getMemoryJobCnt();
        int jobCnt = this.getJobCnt();
        int numberOfTracks = this.getNumberOfTracks();
        int currentHour = this.getCurrentHour();
        int currentMinute = this.getCurrentMinute();

        //************************执行选择的那个作业（开始执行）************************
        //（1）如果当前内存已经满了的话，直接执行完成jobs[pos]即可。
        //（2）如果当前内存未满并且所有未完成的作业都已经调入到了内存，仍然是直接执行完成jobs[pos]即可。
        //（3）如果不是上面两种情况，即内存未满，且存在作业没有调入到内存。这种情况下，要考虑该作业执行过程中，
        //     是否需要调入新作业到内存。由于上面已经完成了作业调入内存的功能，那么这次调入内存的作业也只会有
        //     一个！这一个一定选择此刻尚未完成、未在内存、开始时间最靠前的作业。还需要判断本次作业执行过程中
        //     的时间和将要调入作业的开始时间的关系。
        //     A:本次作业执行完时，将要调入的作业尚未开始。那就需要执行完本次作业。并且把当前时间修改为将要调
        //       入的这个作业的开始时间。
        //     B:本次作业执行过程中，将要调入的作业来了，那就需要把当前时间设置为将要调入的作业的开始时间，并
        //       且设置本次作业的剩余执行时间。
        //     C:本次作业开始执行的时候，将要调入的作业早已经来过了。这种情况直接交给上面的调入内存步骤解决之。

        //针对（1）（2）两种情形
        if(memoryJobCnt == numberOfTracks || memoryJobCnt == jobCnt - this.getFinishedNumber(jobs, jobCnt)){

            //先设置下开始执行的时间
            if(jobs[pos].getFirstExecute() == true){
                jobs[pos].setFirstExecute(false);
                jobs[pos].setExecuteHour(currentHour);
                jobs[pos].setExecuteMinute(currentMinute);
                jobs[pos].setExecuteStartTime(jobs[pos].getExecuteHour()+":"+jobs[pos].getExecuteMinute());
            }

            jobs[pos].setState(true);
            jobs[pos].setEndHour(currentHour + (jobs[pos].getExecuteRemainingTime() + currentMinute)/60);
            jobs[pos].setEndMinute((jobs[pos].getExecuteRemainingTime() + currentMinute) % 60);
            jobs[pos].setInMemory(false);
            memoryJobCnt--;
            this.setMemoryJobCnt(memoryJobCnt);

            //该作业执行完，要设置当前时间
            currentHour = jobs[pos].getEndHour();
            currentMinute = jobs[pos].getEndMinute();

            //再次设置当前时间
            //如果当前内存中的所有作业都执行完之后，还存在内存外尚未执行的作业X，且X的开始时间在当前时间之后，则需要
            //把这样的作业调入内存，那么要把当前时间设置为X的开始时间，为X调入内存做准备。注意这个X就是目前在外存中，
            //且没有完成、且开始时间在目前时间之后，且在所有外存尚未开始执行的作业中开始时间最早。
            if(memoryJobCnt==0 && this.getFinishedNumber(jobs, jobCnt)<jobCnt){
                for(int i = 0; i < jobCnt; i++){
                    if(jobs[i].getInMemory()==false && jobs[i].getState()==false){

                        if(jobs[i].getStartHour()>currentHour || (jobs[i].getStartHour()==currentHour && jobs[i].getStartMinute()>currentMinute)){

                            currentHour = jobs[i].getStartHour();
                            currentMinute = jobs[i].getStartMinute();
                        }
                        break;
                    }
                }
            }
            this.setCurrentHour(currentHour);
            this.setCurrentMinute(currentMinute);
        }else {
            //选中没有完成且不在内存的最先来的作业
            int tmpPos = -1;
            for(int i = 0; i < jobCnt; i++){
                if(jobs[i].getState()==false && jobs[i].getInMemory()==false){
                    tmpPos = i;
                    break;
                }
            }


            //A:本次作业执行完时，将要调入的作业尚未开始
            if(
                    (  (jobs[pos].getExecuteRemainingTime()+ currentMinute)/60 + currentHour < jobs[tmpPos].getStartHour()
                            || (
                            (jobs[pos].getExecuteRemainingTime()+currentMinute)/60 + currentHour == jobs[pos+1].getStartHour()
                                    &&
                                    (jobs[pos].getExecuteRemainingTime()+currentMinute)%60 <= jobs[pos+1].getStartMinute()
                    )
                    )
            ){

                //先设置下开始执行的时间
                if(jobs[pos].getFirstExecute() == true){
                    jobs[pos].setFirstExecute(false);
                    jobs[pos].setExecuteHour(currentHour);
                    jobs[pos].setExecuteMinute(currentMinute);
                    jobs[pos].setExecuteStartTime(jobs[pos].getExecuteHour()+":"+jobs[pos].getExecuteMinute());
                }

                jobs[pos].setState(true);
                jobs[pos].setEndHour(currentHour + (jobs[pos].getExecuteRemainingTime() + currentMinute)/60);
                jobs[pos].setEndMinute((jobs[pos].getExecuteRemainingTime() + currentMinute) % 60);
                jobs[pos].setInMemory(false);
                memoryJobCnt--;
                this.setMemoryJobCnt(memoryJobCnt);
                //该作业执行完，要设置当前时间
                currentHour = jobs[tmpPos].getStartHour();
                currentMinute = jobs[tmpPos].getStartMinute();

                this.setCurrentHour(currentHour);
                this.setCurrentMinute(currentMinute);
            }else if(
                    (  (jobs[pos].getExecuteRemainingTime()+ currentMinute)/60 + currentHour > jobs[tmpPos].getStartHour()
                            || (
                            (jobs[pos].getExecuteRemainingTime()+currentMinute)/60 + currentHour == jobs[pos+1].getStartHour()
                                    &&
                                    (jobs[pos].getExecuteRemainingTime()+currentMinute)%60 > jobs[pos+1].getStartMinute()
                    )
                    )
            ){

                // B:本次作业执行过程中，将要调入的作业来了

                //先设置下开始执行的时间
                if(jobs[pos].getFirstExecute() == true){
                    jobs[pos].setFirstExecute(false);
                    jobs[pos].setExecuteHour(currentHour);
                    jobs[pos].setExecuteMinute(currentMinute);
                    jobs[pos].setExecuteStartTime(jobs[pos].getExecuteHour()+":"+jobs[pos].getExecuteMinute());
                }

                int tmpTime = (jobs[tmpPos].getStartHour() - 1 - currentHour)*60 + 60 + jobs[tmpPos].getStartMinute() - currentMinute;
                jobs[pos].setExecuteRemainingTime(jobs[pos].getExecuteRemainingTime()-tmpTime);
                currentHour = jobs[tmpPos].getStartHour();
                currentMinute = jobs[tmpPos].getStartMinute();
                this.setCurrentHour(currentHour);
                this.setCurrentMinute(currentMinute);
            }

        }

    }


    public void output(){

        Job[] jobs = this.getJobs();
        int jobCnt = this.getJobCnt();


        System.out.println("====================================================================================================================");

        //计算周转时间、带权周转时间、平均周转时间和平均带权周转时间
        //输出
        System.out.println("作业\t进入时间\t估计运行时间（分钟）\t开始时间\t结束时间\t周转时间（分钟）\t带权周转时间");

        double averageTurnOverTime = 0.0;
        double weightedAverageTurnOverTime = 0.0;
        for(int i = 0; i < jobCnt; i++){
            jobs[i].setEndTime(jobs[i].getEndHour()+":"+jobs[i].getEndMinute());

            jobs[i].setEndTime(jobs[i].getEndHour()+":"+jobs[i].getEndMinute());
            //计算周转时间
            int tmpTime = (jobs[i].getEndHour() - jobs[i].getStartHour() -1)*60 + 60 + jobs[i].getEndMinute() - jobs[i].getStartMinute();;

            jobs[i].setTurnOverTime(tmpTime);
            jobs[i].setWeightedTurnOverTime((jobs[i].getTurnOverTime()+0.0)/(0.0+jobs[i].getExecuteTime()));

            averageTurnOverTime += (double)jobs[i].getTurnOverTime();
            weightedAverageTurnOverTime += (double)jobs[i].getWeightedTurnOverTime();
            System.out.println(jobs[i].getName()+"\t"+jobs[i].getStartTime()+"\t\t\t"+jobs[i].getExecuteTime()+"\t\t"+jobs[i].getExecuteStartTime()+"\t\t"+jobs[i].getEndTime()+"\t\t"+
                    jobs[i].getTurnOverTime()+"\t\t\t"+jobs[i].getWeightedTurnOverTime());

        }

        //输出平均周转时间和平均带权周转时间
        System.out.println();
        System.out.println("平均周转时间： "+(averageTurnOverTime/jobCnt)+"分钟");
        System.out.println("平均带权周转时间："+(weightedAverageTurnOverTime/jobCnt));
        System.out.println("====================================================================================================================");


    }


    //计算已经完成的作业数目
    public int getFinishedNumber(Job[] jobs, int jobCnt){

        int num = 0;
        for(int i = 0; i < jobCnt; i++){
            if(jobs[i].getState() == true){
                num ++;
            }
        }
        return num;
    }
}
