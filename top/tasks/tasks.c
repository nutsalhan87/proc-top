#include <linux/sched.h>
#include <linux/sched/mm.h>
#include <linux/sched/cputime.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include "tasks.h"

static void * vrealloc(void *old_ptr, unsigned long long old_size, unsigned long long new_size) {
    void *new_ptr = vmalloc(new_size);
    if (new_size > old_size) {
        memcpy(new_ptr, old_ptr, old_size);
    } else {
        memcpy(new_ptr, old_ptr, new_size);
    }
    vfree(old_ptr);

    return new_ptr;
}

struct tasks get_tasks(void) {
    struct tasks t = {
            .len = 0,
            .rows = vmalloc(100 * sizeof(struct task_row)),
            .size = 100
    };

    return t;
}

void tasks_push_row(struct tasks *t, struct task_row row) {
    t->rows[t->len] = row;
    t->len += 1;
    if (t->len == t->size) {
        t->rows = vrealloc(t->rows,
                          t->size * sizeof(struct task_row),
                          t->size * 2 * sizeof(struct task_row));
        t->size *= 2;
    }
}

struct task_row get_task(struct task_struct *ts, unsigned int mem_total) {
    struct task_row row;
    struct mm_struct *mm;
    unsigned long anon;
    unsigned long file;
    unsigned long shmem;
    unsigned long virt;
    unsigned long long utime;
    unsigned long long stime;

    row.pid = ts->pid;
    row.user_id = ts->real_cred->uid.val;
    row.priority = ts->prio - MAX_RT_PRIO;
    row.nice = task_nice(ts);

    mm = get_task_mm(ts);
    if (mm == NULL) {
        row.virt_kb = 0;
        row.res_kb = 0;
        row.shared_kb = 0;
    } else {
        anon = get_mm_counter(mm, MM_ANONPAGES);
        file = get_mm_counter(mm, MM_FILEPAGES);
        shmem = get_mm_counter(mm, MM_SHMEMPAGES);
        virt = mm->total_vm;
        mmput(mm);
        row.virt_kb = virt << (PAGE_SHIFT - 10);
        row.res_kb = (anon + file + shmem) << (PAGE_SHIFT - 10);
        row.shared_kb = shmem << (PAGE_SHIFT - 10);
    }

    row.state_index = task_state_index(ts);
    row.percent_mem = row.res_kb * 100 / mem_total;

    task_cputime_adjusted(ts, &utime, &stime);
    row.total_time = utime + stime;

    get_task_comm(row.name, ts);

    return row;
}