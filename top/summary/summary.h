#ifndef TOP_SUMMARY_H
#define TOP_SUMMARY_H

struct time_info {
    long long uptime_sec;
};

struct tasks_info {
    unsigned int total;
    unsigned int running;
    unsigned int sleeping;
    unsigned int stopped;
    unsigned int zombie;
};

struct mem_info_kb {
    unsigned int total;
    unsigned int free;
    unsigned int used;
    unsigned int buff_cache;
    unsigned int available;
};

struct summary_info {
    struct time_info time;
    struct tasks_info tasks;
    struct mem_info_kb mem;
};

struct summary_info get_summary(void);

#endif //TOP_SUMMARY_H