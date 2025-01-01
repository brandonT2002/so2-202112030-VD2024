#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SYSCALL_SO2_ADD_MEMORY_LIMIT 557 // Número de la syscall

int main() {
    pid_t process_pid;
    size_t memory_limit;
    int result;

    // Solicitar al usuario el PID del proceso y el límite de memoria
    printf("Ingrese el PID del proceso: ");
    scanf("%d", &process_pid);

    printf("Ingrese el límite de memoria en bytes: ");
    scanf("%zu", &memory_limit);

    // Llamar a la syscall
    result = syscall(SYSCALL_SO2_ADD_MEMORY_LIMIT, process_pid, memory_limit);

    // Verificar el resultado
    if (result == 0) {
        printf("Límite de memoria establecido correctamente para el proceso %d.\n", process_pid);
    } else {
        // Manejar errores
        switch (errno) {
            case EPERM:
                printf("Error: Permisos insuficientes. Se requiere CAP_SYS_ADMIN.\n");
                break;
            case EINVAL:
                printf("Error: Parámetros inválidos (PID o límite de memoria).\n");
                break;
            case ESRCH:
                printf("Error: No se encontró el proceso con PID %d.\n", process_pid);
                break;
            case ENOMEM:
                printf("Error: Memoria insuficiente para establecer la limitación.\n");
                break;
            case 100: // ERROR_EXCEEDS_LIMIT
                printf("Error: El proceso ya excede el límite de memoria especificado.\n");
                break;
            case 101: // ERROR_ALREADY_IN_LIST
                printf("Error: El proceso ya tiene una limitación de memoria configurada.\n");
                break;
            default:
                printf("Error desconocido: %d.\n", errno);
        }
    }

    return 0;
}

