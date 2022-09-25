#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int n_runs, M, N, K;
    bool show;
} Config;

int parse_args(int argc, char *argv[], Config *config)
{
    int read_after = 0;
    (*config).show = false;
    if ((argc == 2)&&(strcmp(argv[1], "--help") == 0)) {
        printf("%s [--show] n_runs M N K - measure time, spent on multiplication of two random matrices with dimensions MxN and NxK\n--show - show all matrices on last run\n", argv[0]);
        return 0;
   } else if (argc == 6) {
        if(strcmp(argv[1], "--show")) {
            printf("Unknown option %s\n", argv[1]);
            return 1;
        }
        (*config).show = true;
        read_after = 1;
   } else if (argc != 5) {
        printf("Invalid parameters\n");
        return 1;
   }
   sscanf(argv[read_after + 1], "%d", &(*config).n_runs);
   sscanf(argv[read_after + 2], "%d", &(*config).M);
   sscanf(argv[read_after + 3], "%d", &(*config).N);
   sscanf(argv[read_after + 4], "%d", &(*config).K);
   return 0;
}

void print_config(Config *config) {
    printf(
        "n_runs:\t%d\nM:\t%d\nN:\t%d\nK:\t%d\n",
        (*config).n_runs,
        (*config).M,
        (*config).N,
        (*config).K
    );
}
