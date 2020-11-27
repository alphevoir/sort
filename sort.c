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

#define BOLD  "\x1b[;1m"
#define RED   "\x1b[31;1m"
#define GREEN "\x1b[32;1m"
#define RESET "\x1b[m"

// typedefs
typedef void sorter(unsigned int *array, const size_t n);

// operations
static int randrange(int min, int max);
// static double randrangef(double min, double max);
static void load(unsigned int* array, const size_t n);
static void shuffle(unsigned int *array, const size_t n);

// testing
static void bench(const char* name, sorter *sorter,
                  const unsigned int *array, const size_t n);

// show
static void print_time(const unsigned int s, const unsigned int ns);

// main
int main(int argc, char *argv[]) {
    size_t n = 1000;
    unsigned int *array;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    array = (unsigned int *) malloc(n * sizeof(*array));
    assert(array != NULL);

    load(array, n);
    shuffle(array, n);
    // rotate(20, array, n);

    printf("%sSorting %lu elements%s\n", BOLD, n, RESET);
    bench("Bubble", &bubble, array, n);
    bench("Selection", &selection, array, n);
    bench("Insertion", &insertion, array, n);
    bench("Insertion smart", &insertion_smart, array, n);
    bench("Shell", &shell, array, n);
    bench("Merge", &merge, array, n);
    bench("Quick", &quick, array, n);
    bench("Heap", &heap, array, n);
    bench("Radix LSD", &radix, array, n);

    free(array);
    return 0;
}

// testing
static void bench(const char* name, sorter *sorter,
                  const unsigned int *array, const size_t n) {
    unsigned int *copy;

    copy = (unsigned int *) malloc(n * sizeof(*array));
    assert(copy != NULL);
    memcpy(copy, array, n * sizeof(*array));

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sorter(copy, n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    size_t len = strlen(name);

    printf("%s%s ", BOLD, name);
    for (size_t i = 0; i < WIDTH - (len + 1); i++) {
        printf(".");
    }
    printf(" %s", RESET);

    for (size_t i = 1; i < n; i++) {
        if (copy[i - 1] > copy[i]) {
            printf("%serror%s\n", RED, RESET);
            // printf("%sReceived:%s \n", BOLD, RESET);
            // print_array("\t", copy, n);
            free(copy);
            return;
        }
    }

    printf("%sok%s", GREEN, RESET);
    printf("\t%sTime taken: ", BOLD);
    print_time(end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
    printf("%s\n", RESET);
}

// operations
static int randrange(int min, int max) {
    return min + (int) ((max - min + 1) * ((double) rand() / (double) RAND_MAX));
}

// static double randrangef(double min, double max) {
//     return min + (max - min) * ((double) rand() / (double) RAND_MAX);
// }

static void load(unsigned int* array, const size_t n) {
    // unsigned int j = 0;

    srand((unsigned int) time(NULL));

    for (size_t i = 0; i < n; i++) {
        array[i] = (unsigned int) rand();

        // if (randrangef(0, 1) > randrangef(0, 1)) {
        //     j += (unsigned int) randrange(0, randrange(0, 1000));
        // }
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

// show
static void print_time(const unsigned int s, const unsigned int ns) {
    static const unsigned int divisions[] = {1000, 1000, 1000, 60};
    static const char *units[] = {"ns", "\u00B5s", "ms", "s"};
    static const size_t divisions_n = 4;
    unsigned int ts = (unsigned int) s, tns = (unsigned int) ns;

    // hmmmmmm :thinking:
    unsigned int *parts;
    parts = (unsigned int *) malloc(divisions_n * sizeof(*parts));
    assert(parts != NULL);

    for (size_t i = 0; i < divisions_n; i++) {
        parts[i] = i != divisions_n - 1 ? tns % divisions[i] : tns;
        tns /= divisions[i];
    }

    for (size_t i = 3; i < divisions_n; i++) {
        parts[i] = i != divisions_n -1 ? ts % divisions[i] : ts;
        ts /= divisions[i];
    }

    for (size_t i = divisions_n; i--; ) {
        if (parts[i]) {
            if (i > 0) {
                printf("%4u.%03u %s", parts[i], parts[i - 1], units[i]);
            } else {
                printf("%4u %s", parts[i], units[i]);
            }

            free(parts);
            return;
        }
    }

    printf("   0 %s", units[0]);
    free(parts);
}
