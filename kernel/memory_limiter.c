#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/memory_limiter.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/mutex.h>

#define ERROR_EXCEEDS_LIMIT -100
#define ERROR_ALREADY_IN_LIST -101


// ===================== SYSCALL 1 =====================
struct memory_limiter_entry {
    struct memory_limitation limit;
    struct list_head list;
};

static LIST_HEAD(memory_limiter_list);

static DEFINE_MUTEX(memory_limiter_mutex);

SYSCALL_DEFINE2(so2_add_memory_limit, pid_t, process_pid, size_t, memory_limit) {
    struct task_struct *task;
    struct memory_limiter_entry *entry, *tmp;

    if (!capable(CAP_SYS_ADMIN)) {
        return -EPERM;
    }

    if (process_pid < 0 || memory_limit < 0) {
        return -EINVAL;
    }

    task = find_task_by_vpid(process_pid);
    if (!task) {
        return -ESRCH;
    }

    mutex_lock(&memory_limiter_mutex);

    list_for_each_entry(tmp, &memory_limiter_list, list) {
        if (tmp->limit.pid == process_pid) {
            mutex_unlock(&memory_limiter_mutex);
            return -ERROR_ALREADY_IN_LIST;
        }
    }

    if (get_mm_rss(task->mm) * PAGE_SIZE > memory_limit) {
        mutex_unlock(&memory_limiter_mutex);
        return -ERROR_EXCEEDS_LIMIT;
    }

    entry = kmalloc(sizeof(*entry), GFP_KERNEL);
    if (!entry) {
        mutex_unlock(&memory_limiter_mutex);
        return -ENOMEM;
    }

    entry->limit.pid = process_pid;
    entry->limit.memory_limit = memory_limit;
    list_add(&entry->list, &memory_limiter_list);

    mutex_unlock(&memory_limiter_mutex);

    return 0;
}

