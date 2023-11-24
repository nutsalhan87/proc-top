#include <linux/seq_file.h>
#include "../summary/summary.h"
#include "../tasks/tasks.h"
#include "printer.h"

static const char *const task_state_array[] = {
        "R (running)",
        "S (sleeping)",
        "D (disk sleep)",
        "T (stopped)",
        "t (tracing stop)",
        "X (dead)",
        "Z (zombie)",
        "P (parked)",
        "I (idle)",
};

static inline const char *get_task_state(unsigned int state_index) {
    return task_state_array[state_index];
}

void print_seq(struct seq_file *m, struct summary_info *si, struct tasks *t) {
    seq_printf(m, "Uptime: %lld:%lld \n", si->time.uptime_sec / 60, si->time.uptime_sec % 60);
    seq_printf(m, "Tasks - total: %u, running: %u, sleeping: %u, stopped: %u, zombie: %u \n",
               si->tasks.total, si->tasks.running, si->tasks.sleeping, si->tasks.stopped, si->tasks.zombie);
    seq_printf(m, "Memory - total: %u kB, free: %u kB, used: %u kB, buffered/cache: %u kB, available: %u kB \n\n",
               si->mem.total, si->mem.free, si->mem.used, si->mem.buff_cache, si->mem.available);
    seq_printf(m, "PID UID PRIO NI VIRT RES SHR S %%MEM +TIME NAME\n");
    for (unsigned long long i = 0; i < t->len; i += 1) {
        seq_printf(
                m,
                "%d %u %d %d %lu kB %lu kB %lu kB %s %hu %llu:%llu %.16s\n",
                t->rows[i].pid,
                t->rows[i].user_id,
                t->rows[i].priority,
                t->rows[i].nice,
                t->rows[i].virt_kb,
                t->rows[i].res_kb,
                t->rows[i].shared_kb,
                get_task_state(t->rows[i].state_index),
                t->rows[i].percent_mem,
                t->rows[i].total_time / 60,
                t->rows[i].total_time % 60,
                t->rows[i].name
        );
    }
}