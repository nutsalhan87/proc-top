#include <linux/types.h>
#include <linux/seq_file.h>

#ifndef TOP_H
#define TOP_H

int get_top(struct seq_file *m, void *v);

#endif //TOP_H