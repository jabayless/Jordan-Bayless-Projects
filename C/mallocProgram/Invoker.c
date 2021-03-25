#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Analyze.h"

int main(int argc, char **argv) {
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s <number-of-iterations>\n", argv[0]);
    	return 1;
    }

    int seed = atoi(argv[1]);
    // set the seed
    srand(seed);
    printf("[Invoker] With seed: %d\n", seed);
    // invoke the function in Analyze.c
    double running_ratio = get_running_ratio();
    printf("[Invoker] Running ratio: %f\n\n", get_running_ratio);
    return 0;
}
