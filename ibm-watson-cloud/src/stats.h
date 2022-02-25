typedef struct Stats Stats;

int stats_init(Stats **pStats);
int stats_free(Stats* stats);
int stats_get_memory(Stats* stats, uint64_t* memory);