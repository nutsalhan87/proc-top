#include <linux/seq_file.h>
#include "../summary/summary.h"
#include "../tasks/tasks.h"

#ifndef TOP_PRINTER_H
#define TOP_PRINTER_H

void print_seq(struct seq_file *m, struct summary_info *si, struct tasks *t);

#endif //TOP_PRINTER_H