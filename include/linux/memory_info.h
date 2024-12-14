#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

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