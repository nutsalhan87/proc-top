#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/printk.h>
#include <linux/seq_file.h>
#include "top/top.h"

static struct proc_dir_entry *top_entry;

static int top_init(void)
{
    top_entry = proc_create_single("top", 644, NULL, get_top);
    if (top_entry == NULL) {
        proc_remove(top_entry);
        pr_err("Error: could not initialize /proc/top\n");
        return -ENOMEM;
    }

    pr_info("/proc/top is created\n");
    return 0;
}

static void top_exit(void)
{
    proc_remove(top_entry);
    pr_info("/proc/top is removed\n");
}

module_init(top_init);
module_exit(top_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nutsalhan87");
MODULE_DESCRIPTION("Partial top output in procfs");