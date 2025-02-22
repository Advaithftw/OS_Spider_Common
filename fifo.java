import java.util.Scanner;

public class fifo {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the number of processes: ");
        int n = sc.nextInt();

        int processes[] = new int[n];
        int burst_time[] = new int[n];
        int arrival_time[] = new int[n];

        for (int i = 0; i < n; i++) {
            processes[i] = i + 1;
            System.out.println("Enter burst time for process " + (i + 1) + ": ");
            burst_time[i] = sc.nextInt();
            System.out.println("Enter arrival time for process " + (i + 1) + ": ");
            arrival_time[i] = sc.nextInt();
        }
        sc.close();

        findavgTime(processes, n, burst_time, arrival_time);
    }

    static void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
        int service_time[] = new int[n];
        service_time[0] = at[0];
        wt[0] = 0;

        for (int i = 1; i < n; i++) {
            int wasted = 0;
            service_time[i] = service_time[i-1] + bt[i-1];
            wt[i] = service_time[i] - at[i];

            if (wt[i] < 0) {
                wasted = Math.abs(wt[i]);
                wt[i] = 0;
            }

            service_time[i] = service_time[i] + wasted;
        }
    }

    static void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
        for (int i = 0; i < n; i++)  
            tat[i] = bt[i] + wt[i];  
    }

    static void findavgTime(int processes[], int n, int bt[], int at[]) {
        int wt[] = new int[n], tat[] = new int[n];

        findWaitingTime(processes, n, bt, wt, at);
        findTurnAroundTime(processes, n, bt, wt, tat);

        System.out.print("Processes " + " Burst Time " + " Arrival Time " + " Waiting Time " + " Turn-Around Time " + " Completion Time \n");
        int total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++) {
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
            int compl_time = tat[i] + at[i];
            System.out.println(i + 1 + "\t\t" + bt[i] + "\t\t" + at[i] + "\t\t" + wt[i] + "\t\t " + tat[i] + "\t\t " + compl_time);
        }

        System.out.print("Average waiting time = " + (float) total_wt / (float) n);
        System.out.print("\nAverage turn around time = " + (float) total_tat / (float) n);
    }

   
}
