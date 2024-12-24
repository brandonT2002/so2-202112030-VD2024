#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

struct memory_info {
    unsigned long total_memory;
    unsigned long free_memory;
    unsigned long used_memory;
    unsigned long cached_memory;
    unsigned long swap_total;
    unsigned long swap_free;
    unsigned long swap_used;
    unsigned long buffered_memory;
};

#define SYS_CAPTURE_MEMORY_SNAPSHOT 548

void print_memory_info(const struct memory_info *mem_info) {
    printf("\n╔═══════════════════════╦════════════════════╗\n");
    printf("║ Memoria               ║ Valores            ║\n");
    printf("╠═══════════════════════╬════════════════════╣\n");
    printf("║ Total Memory          ║ %-18lu ║\n", mem_info->total_memory);
    printf("║ Free Memory           ║ %-18lu ║\n", mem_info->free_memory);
    printf("║ Used Memory           ║ %-18lu ║\n", mem_info->used_memory);
    printf("║ Cached Memory         ║ %-18lu ║\n", mem_info->cached_memory);
    printf("║ Swap Total            ║ %-18lu ║\n", mem_info->swap_total);
    printf("║ Swap Free             ║ %-18lu ║\n", mem_info->swap_free);
    printf("║ Swap Used             ║ %-18lu ║\n", mem_info->swap_used);
    printf("║ Buffered Memory       ║ %-18lu ║\n", mem_info->buffered_memory);
    printf("╚═══════════════════════╩════════════════════╝\n");
}

int main() {
    struct memory_info mem_info;

    if (syscall(SYS_CAPTURE_MEMORY_SNAPSHOT, &mem_info) == -1) {
        perror("Error en capture_memory_snapshot");
        return EXIT_FAILURE;
    }

    print_memory_info(&mem_info);
    return EXIT_SUCCESS;
}
