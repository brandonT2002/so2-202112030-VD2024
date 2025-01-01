#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>

#define SYS_JEFF_TAMALLOC 551

int main() {
    printf("Program for jeff_tamalloc PID: %d\n", getpid());

    printf("Program to Allocate Memory using jeff_tamalloc. Press ENTER to continue...\n");
    getchar();

    size_t total_size = 10 * 1024 * 1024; 

    // Use the jeff_tamalloc syscall
    char *buffer = (char *)syscall(SYS_JEFF_TAMALLOC, total_size);
    if ((long)buffer < 0) {
        perror("jeff_tamalloc failed");
        return 1;
    }
    printf("Allocated 10MB of memory using jeff_tamalloc at address: %p\n", buffer);

    printf("Press ENTER to start reading memory byte by byte...\n");
    getchar();

    srand(time(NULL));

    for (size_t i = 0; i < total_size; i++) {
        char t = buffer[i];
        if (t != 0) {
            printf("ERROR FATAL: Memory at byte %zu was not initialized to 0\n", i);
            return 10;
        }

        char random_letter = 'A' + (rand() % 26);
        buffer[i] = random_letter;

        if (i % (1024 * 1024) == 0 && i > 0) { 
            printf("Checked %zu MB...\n", i / (1024 * 1024));
            sleep(1);
        }
    }

    printf("All memory verified to be zero-initialized. Press ENTER to exit.\n");
    getchar();
    return 0;
}