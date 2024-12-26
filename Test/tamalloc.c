#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SYS_JEFF_TOTAL_MEMORY 553

int main() {
    printf("Program for jeff_total_memory. PID: %d\n", getpid());

    printf("Program to retrieve total system memory using jeff_total_memory. Press ENTER to continue...\n");
    getchar();

    long total_memory = syscall(SYS_JEFF_TOTAL_MEMORY);
    if (total_memory < 0) {
        perror("jeff_total_memory syscall failed");
        return 1;
    }

    printf("Total system memory retrieved using jeff_total_memory: %ld bytes (%.2f MB)\n", 
        total_memory, total_memory / (1024.0 * 1024.0));

    printf("Press ENTER to exit the program...\n");
    getchar();
    return 0;
}
