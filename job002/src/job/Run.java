package job;

/*

	//作者：ccnuacmhdu（CSDN博主）
	//时间：2018/9/28

	************************************本代码：分别在单道和多道批处理系统下实现三种常见的作业调度算法（FCFS，SJF，HRRN）************************************

	【编程语言及工具】Java+记事本+JDK8

	【约定】在一天之内完成，在程序执行过程中，小时只能在0-24，分钟只能在0-59

	【输入】与源代码同文件夹下的in.txt

*/


import java.util.Scanner;
import java.util.Arrays;
import java.util.Comparator;

public class Run{

    public static void main(String[] args){

        Scanner scan = new Scanner(System.in);

        while(true){

            Bp bp = new Bp();

            Job[] jobs = new Job[100];//假定总作业数目不超过100
            bp.setJobs(jobs);

            //数据输入的文件
            String path = "in.txt";
            //输入数据
            bp.input(path);
            //给作业按照时间先后进行排序
            Comparator<Job> jobComparator = new JobComparator();//用泛型，否则报错：-Xlint:unchecked重新编译
            Arrays.sort(jobs, 0, bp.getJobCnt(), jobComparator);

            System.out.println("welcome-----welcome-----welcome-----welcome");
            System.out.print("请输入批处理系统道数： ");
            int numberOfTracks = scan.nextInt();
            bp.setNumberOfTracks(numberOfTracks);

            String jobAlgorithmOption = null;//作业调度算法选择标记
            String processAlgorithmOption = null;//进程调度算法选择标记
            //作业调度算法选择菜单，由用户选择输入
            System.out.println();
            System.out.println("**********************Option**********************");
            System.out.println("1>>>>>>>>>>FCFS(first-come-first-service");
            System.out.println("2>>>>>>>>>>SJF(shortest job first)");
            System.out.println("3>>>>>>>>>>HRRN(Highest Response Ratio Next)");

            System.out.print("请选择作业调度算法编号: ");
            jobAlgorithmOption = scan.next();
            bp.setJobAlgorithmOption(jobAlgorithmOption);

            System.out.print("请选择进程调度算法编号: ");
            processAlgorithmOption = scan.next();
            bp.setProcessAlgorithmOption(processAlgorithmOption);

            while(bp.getFinishedNumber(bp.getJobs(), bp.getJobCnt()) < bp.getJobCnt()){
                //**************************第一步：调度作业到内存**********************************
                switch(bp.getJobAlgorithmOption()){

                    case "1":bp.jobFCFS();
                        break;
                    case "2":bp.jobSJF();
                        break;
                    case "3":bp.jobHRRN();
                        break;
                    default:System.out.println("input error");
                        return;
                }

                //**************************第二步：从内存中选一个作业执行**************************
                int pos;
                switch(bp.getProcessAlgorithmOption()){

                    case "1":pos = bp.processFCFS();
                        break;
                    case "2":pos = bp.processSJF();
                        break;
                    case "3":pos = bp.processHRRN();
                        break;
                    default:System.out.println("input error");
                        return;
                }

                //执行这个作业
                bp.exe(pos);
            }

            //输出
            bp.output();

        }
    }

}
