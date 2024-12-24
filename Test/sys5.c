#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <signal.h>

#define SYSCALL_JEFF_PROCESS_MEMORY 552

struct process_memory_stats {
    pid_t pid;
    unsigned long reserved_kb;
    unsigned long committed_kb;
    unsigned long committed_pct;
    int oom_score;
};

void print_process_table_header() {
    printf("╔════════════╦══════════════════╦══════════════════╦══════════════════════╦════════════╗\n");
    printf("║    PID     ║ Memoria Reservada║ Memoria Utilizada║ % Memoria Utilizada  ║ OOM Score  ║\n");
    printf("╠════════════╬══════════════════╬══════════════════╬══════════════════════╬════════════╣\n");
}

void print_process_table_row(struct process_memory_stats stats) {
    printf("║ %-10d ║ %-16lu ║ %-16lu ║ %-20lu ║ %-10d ║\n",
           stats.pid, stats.reserved_kb, stats.committed_kb, stats.committed_pct, stats.oom_score);
}

void print_process_table_footer() {
    printf("╚════════════╩══════════════════╩══════════════════╩══════════════════════╩════════════╝\n");
}

int process_exists(pid_t pid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d", pid);
    return access(path, F_OK) == 0;
}

void test_process_stats(pid_t pid) {
    struct process_memory_stats stats;

    if (!process_exists(pid)) {
        fprintf(stderr, "Error: El proceso con PID %d no existe o no es accesible.\n", pid);
        return;
    }

    if (syscall(SYSCALL_JEFF_PROCESS_MEMORY, pid, &stats) == 0) {
        print_process_table_header();
        print_process_table_row(stats);
        print_process_table_footer();
    } else {
        perror("Error al obtener estadísticas del proceso");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    if (pid <= 0) {
        fprintf(stderr, "Error: PID no válido. Debe ser un número positivo.\n");
        return 1;
    }

    if (geteuid() != 0) {
        fprintf(stderr, "Error: Este programa debe ejecutarse como superusuario.\n");
        return 1;
    }

    printf("Probando estadísticas del proceso con PID: %d\n", pid);
    test_process_stats(pid);

    return 0;
}


