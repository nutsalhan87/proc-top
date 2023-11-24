#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/vmalloc.h>
#include <linux/printk.h>
#include "top.h"
#include "tasks/tasks.h"
#include "summary/summary.h"
#include "printer/printer.h"

static void modify_summary_tasks_info(struct task_row *tr, struct tasks_info *ti) {
    ti->total += 1;
    if (tr->state_index == 0) {
        ti->running += 1;
    } else if (tr->state_index == 1 || tr->state_index == 2) {
        ti->sleeping += 1;
    } else if (tr->state_index == 3 || tr->state_index == 4) {
        ti->stopped += 1;
    } else if (tr->state_index == 6) {
        ti->zombie += 1;
    }
}

int get_top(struct seq_file *m, void *v) {
    struct summary_info si = get_summary();
    struct tasks t = get_tasks();
    struct task_struct *ts;

    for_each_process(ts)
    {
        struct task_row row = get_task(ts, si.mem.total);
        modify_summary_tasks_info(&row, &si.tasks);
        tasks_push_row(&t, row);
    }

    pr_info("/proc/top: Data collected\n");

    print_seq(m, &si, &t);

    vfree(t.rows);

    return 0;
}