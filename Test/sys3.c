#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

struct io_stats {
    unsigned long long bytes_read;
    unsigned long long bytes_written;
    unsigned long long bytes_read_disk;
    unsigned long long bytes_written_disk;
    unsigned long long io_wait_time;
};

#define SYS_GET_IO_THROTTLE 550

void print_io_stats(const struct io_stats *stats, pid_t pid) {
    // Ajustar el formato de la tabla para una correcta alineación
    printf("\n╔══════════════════════════════════════╦══════════════════════════════════════╗\n");
    printf("║ Estadísticas                         ║ Valores                              ║\n");
    printf("╠══════════════════════════════════════╬══════════════════════════════════════╣\n");
    printf("║ PID                                  ║ %-36d ║\n", pid);
    printf("║ Bytes Read                           ║ %-36llu ║\n", stats->bytes_read);
    printf("║ Bytes Written                        ║ %-36llu ║\n", stats->bytes_written);
    printf("║ Bytes Read from Disk                 ║ %-36llu ║\n", stats->bytes_read_disk);
    printf("║ Bytes Written to Disk                ║ %-36llu ║\n", stats->bytes_written_disk);
    printf("║ IO Wait Time                         ║ %-36llu ║\n", stats->io_wait_time);
    printf("╚══════════════════════════════════════╩══════════════════════════════════════╝\n");
}

int main() {
    struct io_stats stats;
    pid_t pid = getpid();

    if (syscall(SYS_GET_IO_THROTTLE, pid, &stats) == -1) {
        perror("Error en get_io_throttle");
        return EXIT_FAILURE;
    }

    print_io_stats(&stats, pid);
    return EXIT_SUCCESS;
}
