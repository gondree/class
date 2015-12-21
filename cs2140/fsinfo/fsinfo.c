#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

const struct option long_opts[] = {
    {"help", no_argument, 0, 'h'},
    {"verbose", no_argument, 0, 'v'},
    {0, 0, 0, 0}
};

const char *opts_desc[] = {
    ", to display this usage message.",
    ", for verbose output.",
};

void usage(const char* arg)
{
    int i;
    printf("Usage: %s [OPTIONS] ARGS, where\n", arg);
    printf("  ARGS: filenames that will be used as arguments\n");
    printf("  OPTIONS:\n");
    for (i = 0; i < sizeof(long_opts) / sizeof(struct option) - 1; i++) {
        printf("\t-%c, --%s%s\n",
            long_opts[i].val, long_opts[i].name, opts_desc[i]);
    }    
}

// prototypes
void show_stat(const char* path);
void show_dir(const char* path);
void show_fs(const char* path);

// global variables
int verbose = 0;

int main(int argc, char *argv[])
{
    int opt, i;

    while( -1 != (opt = getopt_long(argc, argv, "hv", long_opts, &i)) ) {
        switch(opt) {
            case 'h':
                usage(argv[0]);
                exit(0);
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Invalid option.\n");
                usage(argv[0]);
                exit(-1);
                break;
        }
    } // while
    return 0;
}

