#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/sched.h>
#include <linux/time64.h>
#include <linux/timekeeping.h>
#include <linux/time_namespace.h>
#include "summary.h"

static struct time_info get_time_info(void) {
    struct time_info ti;
    struct timespec64 uptime;

    ktime_get_boottime_ts64(&uptime);
    timens_add_boottime(&uptime);

    ti.uptime_sec = uptime.tv_sec;

    return ti;
}

static struct tasks_info get_tasks_info(void) {
    struct tasks_info ti = {
            .total = 0,
            .running = 0,
            .sleeping = 0,
            .stopped = 0,
            .zombie = 0
    };

    return ti;
}

static struct mem_info_kb get_mem_info(void) {
    struct sysinfo si;
    long cached;
    long available;
    struct mem_info_kb mi;

    si_meminfo(&si);
    cached = global_node_page_state(NR_FILE_PAGES) - total_swapcache_pages() - si.bufferram;
    if (cached < 0) {
        cached = 0;
    }
    available = si_mem_available();

    mi.total = si.totalram << (PAGE_SHIFT - 10);
    mi.free = si.freeram << (PAGE_SHIFT - 10);
    mi.used = (si.totalram - si.freeram - si.bufferram - cached) << (PAGE_SHIFT - 10);
    mi.buff_cache = (si.bufferram + cached) << (PAGE_SHIFT - 10);
    mi.available = available << (PAGE_SHIFT - 10);

    return mi;
}

struct summary_info get_summary(void) {
    struct summary_info si = {
        .time = get_time_info(),
        .tasks = get_tasks_info(),
        .mem = get_mem_info(),
    };

    return si;
}
