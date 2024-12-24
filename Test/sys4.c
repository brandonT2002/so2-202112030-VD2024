#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

// Definir el número de la syscall (551 en tu caso)
#define JEFF_TAMALLOC_SYSCALL 551

int main() {
    size_t size = 4096; // Tamaño de memoria a reservar (por ejemplo, 4 KB)
    void *addr;

    // Invocar la syscall jeff_tamalloc
    addr = (void *)syscall(JEFF_TAMALLOC_SYSCALL, size);

    // Verificar si hubo error
    if ((long)addr < 0) {
        perror("Error al llamar a jeff_tamalloc");
        return 1;
    }

    // Imprimir dirección de memoria reservada
    printf("Memoria reservada en la dirección: %p\n", addr);

    // Nota: El programa no usa `munmap` aquí porque la memoria asignada es anónima.
    return 0;
}

