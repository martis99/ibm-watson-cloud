#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <argp.h>
#include <signal.h>
#include <sys/file.h>
#include <fcntl.h>

#include "device.h"
#include "stats.h"

const char *argp_program_version = "ibm-watson-cloud 1.0";
const char *LOCKFILE = "/var/lock/ibm-watson-cloud.lock";

volatile int interrupt = 0;

void handle_signal(int signo) {
    signal(SIGINT, NULL);
    interrupt = 1;
}


int file_lock(const char* file, int *fd) {
    if ((*fd = open(file, O_RDWR | O_CREAT)) == -1) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    if (flock(*fd, LOCK_EX | LOCK_NB) == -1) {
        fprintf(stderr, "File is alrealy locked\n");
        return 1;
    }
    return 0;
}

void file_unlock(int fd) {
    if (flock(fd, LOCK_UN) == -1) {
        fprintf(stderr, "Failed to unlock file\n");
        return 1;
    }
    close(fd);
    fprintf(stdout, "Unlocked\n");
    return 0;
}

typedef struct Opts {
    char *orgId;
    char *typeId;
    char *deviceId;
    char *token;
    int interval;
} Opts;

static struct argp_option options[] =
{
  {"org", 'o', "", 0, "orgId"},
  {"type", 't', "", 0, "typeId"},
  {"device", 'd', "", 0, "deviceId"},
  {"auth", 'a', "", 0, "auth token"},
  {"interval", 'i', "2", 0, "interval"},
  {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  Opts *opts = state->input;

  switch (key)
    {
    case 'o':
        opts->orgId = arg;
        break;
    case 't':
        opts->typeId = arg;
        break;
    case 'd':
        opts->deviceId = arg;
        break;
    case 'a':
        opts->token = arg;
        break;
    case 'i':
        opts->interval = atoi(arg);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

int main(int argc, char **argv) {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    int lock_fd;
    if(file_lock(LOCKFILE, &lock_fd) != 0) {
        return 1;
    }

    Opts opts;
    opts.orgId = "";
    opts.typeId = "";
    opts.deviceId = "";
    opts.token = "";
    opts.interval = 2;

    struct argp argp = {options, parse_opt, "", "ibm-watson-cloud -- A program to send data to ibm watson cloud."};
    argp_parse(&argp, argc, argv, 0, 0, &opts);

    Stats* stats;
    if(stats_init(&stats) != 0) {
        return 1;
    }

    Device* device;
    if(device_connect(&device, opts.orgId, opts.typeId, opts.deviceId, opts.token) != 0) {
        return 1;
    }

    char data[256];
    uint64_t memory;
    
    while(!interrupt) {
        if(stats_get_memory(stats, &memory) != 0) {
            return 1;
        }
        snprintf(data, sizeof(data) / sizeof(char), "{\"memory\": %lld}", memory);
        device_send_data(device, data);
        sleep(opts.interval);
    }

   if(stats_free(stats) != 0) {
       return 1;
   }

    if(device_disconnect(device) != 0) {
        return 1;
    }

    file_unlock(lock_fd);
    return 0;
}
