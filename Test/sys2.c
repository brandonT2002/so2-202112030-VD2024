#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

struct syscall_usage {
    unsigned long count;
    struct timespec time_last_used;
};

#define SYS_TRACK_SYSCALL_USAGE 549
#define MAX_SYS_CALLS 1024

void print_syscall_usage(const struct syscall_usage *statistics, int max_syscalls) {
    printf("\n╔════════════╦══════════════╦════════════════════════════════╗\n");
    printf("║ Syscall ID ║ Contador     ║ Ultimo uso                     ║\n");
    printf("╠════════════╬══════════════╬════════════════════════════════╣\n");
    for (int i = 0; i < max_syscalls; ++i) {
        char time_buffer[50];
        int length = snprintf(time_buffer, sizeof(time_buffer), "%lld.%09ld",
                                (long long)statistics[i].time_last_used.tv_sec,
                                statistics[i].time_last_used.tv_nsec);

        int padding = 31 - length;
        if (padding < 0) padding = 0;

        printf("║ %-10d ║ %-12lu ║ %s%*s║\n",
                i,
                statistics[i].count,
                time_buffer,
                padding, "");
    }
    printf("╚════════════╩══════════════╩════════════════════════════════╝\n");
}

int main() {
    struct syscall_usage statistics[MAX_SYS_CALLS];

    if (syscall(SYS_TRACK_SYSCALL_USAGE, statistics) == -1) {
        perror("Error en track_syscall_usage");
        return EXIT_FAILURE;
    }

    print_syscall_usage(statistics, 10);
    return EXIT_SUCCESS;
}
