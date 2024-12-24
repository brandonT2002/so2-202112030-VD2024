#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SYSCALL_JEFF_TOTAL_MEMORY 553

struct total_memory_stats {
    unsigned long total_reserved_mb;
    unsigned long total_committed_mb;
};

void print_total_table(struct total_memory_stats stats) {
    printf("╔════════════════════╦════════════════════╗\n");
    printf("║ Memoria Total Res. ║ Memoria Total Util.║\n");
    printf("╠════════════════════╬════════════════════╣\n");
    printf("║ %-18lu ║ %-18lu ║\n", stats.total_reserved_mb, stats.total_committed_mb);
    printf("╚════════════════════╩════════════════════╝\n");
}

void test_total_stats() {
    struct total_memory_stats stats;

    if (syscall(SYSCALL_JEFF_TOTAL_MEMORY, &stats) == 0) {
        print_total_table(stats);
    } else {
        perror("Error al obtener estadísticas globales");
    }
}

int main() {
    printf("Probando estadísticas globales del sistema:\n");
    test_total_stats();

    return 0;
}
