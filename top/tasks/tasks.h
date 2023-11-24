#include <linux/types.h>

#ifndef TOP_TASKS_H
#define TOP_TASKS_H

struct tasks {
    unsigned long long len;
    unsigned long long size;
    struct task_row *rows;
};

struct task_row {
    int pid;
    unsigned int user_id;
    int priority;
    int nice;
    unsigned long virt_kb;
    unsigned long res_kb;
    unsigned long shared_kb;
    unsigned int state_index;
    unsigned short percent_mem;
    unsigned long long total_time;
    char name[16];
};

struct tasks get_tasks(void);

void tasks_push_row(struct tasks *t, struct task_row row);

struct task_row get_task(struct task_struct *ts, unsigned int mem_total);

#endif //TOP_TASKS_H