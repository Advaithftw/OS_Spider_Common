#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

struct Deadlock {
    int n; 
    int m; 
    int need[MAX_PROCESSES][MAX_RESOURCES]; 
    int max[MAX_PROCESSES][MAX_RESOURCES];  
    int alloc[MAX_PROCESSES][MAX_RESOURCES]; 
    int avail[MAX_RESOURCES]; 
};


void initializeValues(struct Deadlock *deadlock) {
    printf("Enter the number of processes: ");
    scanf("%d", &deadlock->n);

    printf("Enter the number of resources: ");
    scanf("%d", &deadlock->m);

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < deadlock->n; i++) {
        for (int j = 0; j < deadlock->m; j++) {
            scanf("%d", &deadlock->alloc[i][j]);
        }
    }

    printf("Enter the MAX Matrix:\n");
    for (int i = 0; i < deadlock->n; i++) {
        for (int j = 0; j < deadlock->m; j++) {
            scanf("%d", &deadlock->max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < deadlock->m; i++) {
        scanf("%d", &deadlock->avail[i]);
    }
}


void calculateNeed(struct Deadlock *deadlock) {
    for (int i = 0; i < deadlock->n; i++) {
        for (int j = 0; j < deadlock->m; j++) {
            deadlock->need[i][j] = deadlock->max[i][j] - deadlock->alloc[i][j];
        }
    }
}


bool isSafe(struct Deadlock *deadlock) {
    int work[MAX_RESOURCES];
    bool visited[MAX_PROCESSES] = { false };

    for (int i = 0; i < deadlock->m; i++) {
        work[i] = deadlock->avail[i];
    }

    int count = 0;
    while (count < deadlock->n) {
        bool flag = false;
        for (int i = 0; i < deadlock->n; i++) {
            if (!visited[i]) {
                int j;
                for (j = 0; j < deadlock->m; j++) {
                    if (deadlock->need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == deadlock->m) {
                    visited[i] = true;
                    flag = true;
                    for (j = 0; j < deadlock->m; j++) {
                        work[j] += deadlock->alloc[i][j];
                    }
                    count++;
                }
            }
        }
        if (!flag) {
            break;
        }
    }

    if (count < deadlock->n) {
        printf("The System is UnSafe!\n");
        return false;
    } else {
        printf("The System is Safe\n");
        return true;
    }
}

int main() {
    struct Deadlock deadlock;

    initializeValues(&deadlock);
    calculateNeed(&deadlock);
    isSafe(&deadlock);

    return 0;
}
