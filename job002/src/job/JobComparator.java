package job;

import java.util.Comparator;

//比较器实现Job对象排序，根据时间先后顺序进行
public class JobComparator implements Comparator<Job>{

    public int compare(Job job1, Job job2){

        if(job1.getStartHour() < job2.getStartHour()){
            return -1;
        }else if(job1.getStartHour() > job2.getStartHour()){
            return 1;
        }else{
            if(job1.getStartMinute() < job2.getStartMinute()){
                return -1;
            }else if(job1.getStartMinute() > job2.getStartMinute()){
                return 1;
            }else{
                return 0;
            }
        }
    }
}


