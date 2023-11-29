package Process;     //此接口用于初始化排序
                     // 根据随机生成的进程优先级数对进程进行排序

import java.util.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

public class Processsort {
    public ArrayList<PCB> ProcessSort(ArrayList<PCB> notSortProcessList){



        //Map集合，用于存储进程的优先级数和该进程在未排序集合中的位置position
        //第一个Integer是该进程在notSortProcessList中的index，第二个Integer是该进程的优先级数（不能重复）
        Map<Integer, Integer> notSortIndexAndPriority = new HashMap<Integer, Integer>();

        //排序后的进程集合
        ArrayList<PCB> alreadySortProcessList = new ArrayList<PCB>();
        for (int i = 0; i < notSortProcessList.size(); i++) {
            int priority = notSortProcessList.get(i).getPriority(); //取出未排序集合中进程的优先级数
            notSortIndexAndPriority.put(i, priority);
        }

        //HashMap根据Value值进行排序
        List<Map.Entry<Integer, Integer>> list = new ArrayList<>(notSortIndexAndPriority.entrySet());
        list.sort(new Comparator<Entry<Integer, Integer>>() {

            @Override
            public int compare(Entry<Integer, Integer> o1, Entry<Integer, Integer> o2) {
                return o2.getValue().compareTo(o1.getValue());
            }
        });

        for (Map.Entry sEntry : list) {
            PCB pcb = notSortProcessList.get((int) sEntry.getKey());
            alreadySortProcessList.add(pcb);
        }
        return alreadySortProcessList;
    }
}
