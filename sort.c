#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "sorts/common.h"
#include "sorts/bubble.h"
#include "sorts/selection.h"
#include "sorts/insertion.h"
#include "sorts/shell.h"
#include "sorts/merge.h"
#include "sorts/quick.h"
#include "sorts/heap.h"
#include "sorts/radix.h"

// defines
#define WIDTH 64

#define MU    "\u00B5"
#define BOLD  "\x1b[;1m"
#define RED   "\x1b[31;1m"
#define GREEN "\x1b[32;1m"
#define RESET "\x1b[m"

// typedefs
typedef void sorter(unsigned int *array, const size_t n);

// operations
static int randrange(int min, int max);
static double randrangef(double min, double max);
static void load(unsigned int* array, const size_t n);
static void shuffle(unsigned int *array, const size_t n);

// testing
static void bench(const char* name, sorter *sorter,
                  const unsigned int *array, const unsigned int *sorted, const size_t n);

// main
int main(int argc, char *argv[]) {
    size_t n = 1000;
    unsigned int *array, *sorted;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    array = (unsigned int *) malloc(n * sizeof(*array));
    sorted = (unsigned int *) malloc(n * sizeof(*sorted));
    assert((array != NULL) && (sorted != NULL));

    load(array, n);
    memcpy(sorted, array, n * sizeof(*array));

    shuffle(array, n);
    // rotate(20, array, n);

    // bench("Bubble", &bubble, array, sorted, n);
    // bench("Selection", &selection, array, sorted, n);
    // bench("Insertion", &insertion, array, sorted, n);
    // bench("Insertion smart", &insertion_smart, array, sorted, n);
    // bench("Shell", &shell, array, sorted, n);
    bench("Merge", &merge, array, sorted, n);
    bench("Quick", &quick, array, sorted, n);
    bench("Heap", &heap, array, sorted, n);
    bench("Radix LSD", &radix, array, sorted, n);

    free(array);
    free(sorted);
    return 0;
}

// testing
static void bench(const char* name, sorter *sorter,
                  const unsigned int *array, const unsigned int *sorted, const size_t n) {
    unsigned int *copy;

    copy = (unsigned int *) malloc(n * sizeof(*copy));
    assert(copy != NULL);
    memcpy(copy, array, n * sizeof(*array));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sorter(copy, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    unsigned int runtime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    size_t len = strlen(name);
    printf("%s%s%s ", BOLD, name, RESET);

    for (size_t i = 0; i < WIDTH - (len + 1); i++) {
        printf("%s.%s", BOLD, RESET);
    }

    for (size_t i = 0; i < n; i++) {
        if (copy[i] != sorted[i]) {
            printf(" %serror%s\n", RED, RESET);
            printf("%sReceived:%s \n", BOLD, RESET);
            print_array("\t", copy, n);
            free(copy);
            return;
        }
    }

    printf(" %sok%s\t%sTime taken: %u%ss%s\n", GREEN, RESET, BOLD, runtime, MU, RESET);
    free(copy);
}

// operations
static int randrange(int min, int max) {
    return min + (int) ((max - min + 1) * ((double) rand() / (double) RAND_MAX));
}

static double randrangef(double min, double max) {
    return min + (max - min) * ((double) rand() / (double) RAND_MAX);
}

static void load(unsigned int* array, const size_t n) {
    unsigned int j = 0;

    srand((unsigned int) time(NULL));

    for (size_t i = 0; i < n; i++) {
        array[i] = j;

        if (randrangef(0, 1) > randrangef(0, 1)) {
            j += (unsigned int) randrange(0, randrange(0, 1000));
        }
    }
}

static void shuffle(unsigned int *array, const size_t n) {
    srand((unsigned int) time(NULL));

    // nothing to shuffle at n
    for (size_t i = 0; i < n - 1; i++) {
        size_t j = randrange(i, n - 1);
        swap(&array[i], &array[j]);
    }
}

