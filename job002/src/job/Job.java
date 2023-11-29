package job;

import java.util.Comparator;

public class Job{

    private String name;//作业名称
    private String startTime;//作业进入时间
    private String endTime;//作业完成时间

    private int executeTime;//作业估计运行时间
    private int executeRemainingTime;//作业估计运行时间的剩余时间


    private int startHour;//进入时间对应的小时
    private int startMinute;//进入时间对应的分钟

    private int executeHour;//开始执行时间对应的小时
    private int executeMinute;//开始执行时间对应的分钟
    private String executeStartTime;//开始执行的时间

    private int endHour;//结束时间对应的小时
    private int endMinute;//结束时间对应的分钟


    private int turnOverTime;//周转时间，用分钟记
    private double weightedTurnOverTime;//带权周转时间

    private boolean state;//标记该作业是否执行完成
    private boolean inMemory;//标记作业是否在内存

    private boolean firstExecute;//标记是否是第一次执行

    public void setName(String name){
        this.name = name;
    }
    public String getName(){
        return this.name;
    }

    public void setStartTime(String startTime){
        this.startTime = startTime;
    }
    public String getStartTime(){
        return this.startTime;
    }

    public void setEndTime(String endTime){
        this.endTime = endTime;
    }
    public String getEndTime(){
        return this.endTime;
    }

    public void setExecuteTime(int executeTime){
        this.executeTime = executeTime;
    }
    public int getExecuteTime(){
        return this.executeTime;
    }

    public void setExecuteRemainingTime(int executeRemainingTime){
        this.executeRemainingTime = executeRemainingTime;
    }
    public int getExecuteRemainingTime(){
        return this.executeRemainingTime;
    }

    public void setStartHour(int startHour){
        this.startHour = startHour;
    }
    public int getStartHour(){
        return this.startHour;
    }

    public void setStartMinute(int startMinute){
        this.startMinute = startMinute;
    }
    public int getStartMinute(){
        return this.startMinute;
    }

    public void setEndHour(int endHour){
        this.endHour = endHour;
    }
    public int getEndHour(){
        return this.endHour;
    }

    public void setEndMinute(int endMinute){
        this.endMinute = endMinute;
    }
    public int getEndMinute(){
        return this.endMinute;
    }

    public void setTurnOverTime(int turnOverTime){
        this.turnOverTime = turnOverTime;
    }
    public int getTurnOverTime(){
        return this.turnOverTime;
    }

    public void setWeightedTurnOverTime(double weightedTurnOverTime){
        this.weightedTurnOverTime = weightedTurnOverTime;
    }
    public double getWeightedTurnOverTime(){
        return this.weightedTurnOverTime;
    }

    public void setState(boolean state){
        this.state = state;
    }
    public boolean getState(){
        return this.state;
    }

    public void setInMemory(boolean inMemory){
        this.inMemory = inMemory;
    }
    public boolean getInMemory(){
        return this.inMemory;
    }

    public void setExecuteHour(int executeHour){
        this.executeHour = executeHour;
    }
    public int getExecuteHour(){
        return this.executeHour;
    }

    public void setExecuteMinute(int executeMinute){
        this.executeMinute = executeMinute;
    }
    public int getExecuteMinute(){
        return this.executeMinute;
    }

    public void setFirstExecute(boolean firstExecute){
        this.firstExecute = firstExecute;
    }
    public boolean getFirstExecute(){
        return this.firstExecute;
    }

    public void setExecuteStartTime(String executeStartTime){
        this.executeStartTime = executeStartTime;
    }
    public String getExecuteStartTime(){
        return this.executeStartTime;
    }


    //测试
	/*
	public static void main(String[] args){
		Job job = new Job();
		job.setName("job");
		job.setStartTime("8:00");
		job.setEndTime("10:00");
		job.setCurrentTime("8:00");
		job.setExecuteTime(50);
		job.setExecuteRemainingTime(50);
		System.out.println(job.getName()+" "+job.getStartTime()+" "+job.getEndTime()+" "+
			job.getCurrentTime()+" "+job.getExecuteTime()+" "+job.getExecuteRemainingTime());


	}
	*/

}



