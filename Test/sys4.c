#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define JEFF_TAMALLOC_SYSCALL 551

void print_table_header() {
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                Información de la Memoria Reservada         ║\n");
    printf("╠════════════════════╦═══════════════════════════════════════╣\n");
    printf("║ Dirección          ║ Tamaño Reservado (bytes)              ║\n");
    printf("╠════════════════════╬═══════════════════════════════════════╣\n");
}

void print_table_row(void *addr, size_t size) {
    printf("║ %-18p ║ %-37zu ║\n", addr, size);
}

void print_table_footer() {
    printf("╚════════════════════╩═══════════════════════════════════════╝\n");
}

int main() {
    size_t size = 4096;
    void *addr;

    addr = (void *)syscall(JEFF_TAMALLOC_SYSCALL, size);

    if ((long)addr < 0) {
        perror("Error al llamar a jeff_tamalloc");
        return 1;
    }

    print_table_header();
    print_table_row(addr, size);
    print_table_footer();

    return 0;
}

