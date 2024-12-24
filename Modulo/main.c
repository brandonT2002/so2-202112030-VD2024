#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>          // Para acceder a la información de la CPU
#include <linux/fs.h>             // Para operaciones de archivo
#include <linux/stat.h>           // Para obtener estadísticas
#include <linux/seq_file.h>       // Para interactuar con /proc
#include <linux/proc_fs.h>        // Para crear archivos en /proc
#include <linux/mm.h>             // Para memoria
#include <linux/sysinfo.h>        // Para obtener memoria libre

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brandon Tejaxún");
MODULE_DESCRIPTION("Modulo para leer informacion de memoria y CPU");
MODULE_VERSION("1.0");

#define PROC_NAME "sysinfo_202112030"

static int proc_show(struct seq_file *m, void *v)
{
    unsigned long free_mem;
    struct sysinfo si;
    char buffer[256];
    struct file *f;
    ssize_t bytes_read;
    loff_t pos = 0;

    f = filp_open("/proc/stat", O_RDONLY, 0);
    if (IS_ERR(f)) {
        seq_printf(m, "Error: No se puede abrir /proc/stat. Error: %ld\n", PTR_ERR(f));
        return 0;
    }

    bytes_read = kernel_read(f, buffer, sizeof(buffer) - 1, &pos);
    if (bytes_read < 0) {
        seq_printf(m, "Error al leer /proc/stat. Error: %ld\n", bytes_read);
        filp_close(f, NULL);
        return 0;
    }

    buffer[bytes_read] = '\0';

    unsigned long user_time, nice_time, system_time, idle_time, iowait_time;
    if (sscanf(buffer, "cpu  %lu %lu %lu %lu %lu", &user_time, &nice_time, &system_time, &idle_time, &iowait_time) == 5) {
        seq_printf(m, "╔═════════════════════╦════════════╗\n");
        seq_printf(m, "║     Estadística     ║   Valor    ║\n");
        seq_printf(m, "╠═════════════════════╬════════════╣\n");
        seq_printf(m, "║ user_time           ║ %10lu ║\n", user_time);
        seq_printf(m, "║ nice_time           ║ %10lu ║\n", nice_time);
        seq_printf(m, "║ system_time         ║ %10lu ║\n", system_time);
        seq_printf(m, "║ idle_time           ║ %10lu ║\n", idle_time);
        seq_printf(m, "║ iowait_time         ║ %10lu ║\n", iowait_time);
        seq_printf(m, "╠═════════════════════╬════════════╣\n");
    }

    si_meminfo(&si);
    free_mem = si.freeram * si.mem_unit;

    seq_printf(m, "║ free_memory         ║ %10lu ║\n", free_mem);
    seq_printf(m, "╚═════════════════════╩════════════╝\n");

    filp_close(f, NULL);

    return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show, NULL);
}

static const struct proc_ops proc_fops = {
    .proc_open = proc_open,
    .proc_read = seq_read,
    .proc_release = single_release,
};

// Iniciar módulo
static int __init my_module_init(void)
{
    proc_create(PROC_NAME, 0, NULL, &proc_fops);
    printk(KERN_INFO "Módulo %s cargado.\n", PROC_NAME);
    return 0;
}

// Eliminar módulo
static void __exit my_module_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "Módulo %s descargado.\n", PROC_NAME);
}

module_init(my_module_init);
module_exit(my_module_exit);
