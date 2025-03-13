#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3  // Define number of child processes

int main() {
    pid_t pids[NUM_CHILDREN];
    printf("Parent Process ID: %d\n", getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pids[i] == 0) {  // Child process
            printf("Child Process Created: PID = %d, Parent PID = %d\n", getpid(), getppid());

            // 🔥 Allocate dynamic memory in the child process
            void *mem = malloc(1024 * 10); // 10 KB
            if (!mem) {
                perror("Memory allocation failed in child");
                exit(1);
            }

            // 🔥 Allocate memory for grandchild PID
            pid_t *grandchild_pid = (pid_t *)malloc(sizeof(pid_t));
            if (grandchild_pid == NULL) {
                perror("Memory allocation failed for grandchild");
                free(mem); // Free child memory before exiting
                exit(1);
            }

            // 🔥 Create grandchild process
            *grandchild_pid = fork();
            if (*grandchild_pid < 0) {
                perror("Fork failed for grandchild");
                free(grandchild_pid);
                free(mem);
                exit(1);
            } else if (*grandchild_pid == 0) {  // Grandchild process
                printf("Grandchild Created: PID = %d, Parent PID = %d\n", getpid(), getppid());
                
                // Allocate memory in grandchild
                void *grandchild_mem = malloc(1024 * 5); // 5 KB
                if (!grandchild_mem) {
                    perror("Memory allocation failed in grandchild");
                    free(grandchild_pid);
                    exit(1);
                }

                sleep(5);  // Keep grandchild alive for kernel module detection
                free(grandchild_mem);
                free(grandchild_pid); // Free memory before exiting
                exit(0);
            }

            // Child waits for its grandchild
            waitpid(*grandchild_pid, NULL, 0);
            free(grandchild_pid); // Free grandchild PID memory in child
            free(mem);  // Free allocated memory in child
            exit(0);
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < NUM_CHILDREN; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}

