#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <libubox/blobmsg_json.h>
#include <libubus.h>

#include "stats.h"

struct Stats {
    struct ubus_context *ctx;
};

enum {
    TOTAL_MEMORY,
    FREE_MEMORY,
    SHARED_MEMORY,
    BUFFERED_MEMORY,
    __MEMORY_MAX
};

enum {
    MEMORY_DATA,
    __INFO_MAX
};

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
    [TOTAL_MEMORY] = {.name="total", .type=BLOBMSG_TYPE_INT64},
    [FREE_MEMORY] = {.name="free", .type=BLOBMSG_TYPE_INT64},
    [SHARED_MEMORY] = {.name="shared", .type=BLOBMSG_TYPE_INT64},
    [BUFFERED_MEMORY] = {.name="buffered", .type=BLOBMSG_TYPE_INT64}
};

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
    [MEMORY_DATA] = { .name="memory", .type=BLOBMSG_TYPE_TABLE}
};

static void board_cb(struct ubus_request *req, int type, struct blob_attr *msg) {
    uint64_t *used_memory = (uint64_t*)req->priv;
    struct blob_attr *tb[__INFO_MAX];
    struct blob_attr *memory[__MEMORY_MAX];

    blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));
    if(!tb[MEMORY_DATA]) {
        fprintf(stderr, "No memory data received\n");
        return;
    }

    blobmsg_parse(memory_policy, __MEMORY_MAX, memory, blobmsg_data(tb[MEMORY_DATA]), blobmsg_data_len(tb[MEMORY_DATA]));
    *used_memory = blobmsg_get_u64(memory[TOTAL_MEMORY]) - blobmsg_get_u64(memory[FREE_MEMORY]);
}

int stats_init(Stats **pStats) {
    *pStats = (Stats*)malloc(sizeof(Stats));
    Stats* stats = *pStats;
    stats->ctx = ubus_connect(NULL);
    if(!stats->ctx) {
        fprintf(stderr, "Failed to connect to ubus\n");
        return 1;
    }

    return 0;

}

int stats_free(Stats* stats) {
    ubus_free(stats->ctx);
    free(stats);
    return 0;
}

int stats_get_memory(Stats* stats, uint64_t* memory) {
    uint32_t id;
    if(ubus_lookup_id(stats->ctx, "system", &id) || ubus_invoke(stats->ctx, id, "info", NULL, board_cb, memory, 3000)) {
        fprintf(stderr, "Cannot request memory info from procd\n");
        return 1;
    }
    return 0;
}