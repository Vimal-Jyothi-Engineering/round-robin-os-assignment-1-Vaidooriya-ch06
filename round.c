#include <stdio.h>
#include <string.h>

struct process {
    char pid[10];
    int at, bt, rt;
    int ct, wt, tat;
};

int main() {
    int n, time = 0, done = 0, quantum;
    scanf("%d", &n);

    struct process p[20];
    int total_wt = 0, total_tat = 0;

    // Input processes
    for(int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }

    scanf("%d", &quantum); // Time quantum

    int completed[20] = {0};
    while(done < n) {
        int flag = 0;
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time) {
                flag = 1;
                if(p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].at - p[i].bt;
                    p[i].tat = p[i].wt + p[i].bt;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                    p[i].rt = 0;
                    done++;
                }
            }
        }
        if(!flag) time++; // If no process is ready, increment time
    }

    // Print results
    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].wt);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].tat);

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
