#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "common.h"
#include "radix.h"

// won't handle negative ints for now
static void radixsort(unsigned int *array, unsigned int *working, const size_t n);

void radix(unsigned int *array, const size_t n) {
    unsigned int *working;

    working = (unsigned int *) malloc(n * sizeof(*working));
    assert(working != NULL);

    radixsort(array, working, n);
    free(working);
}

static void radixsort(unsigned int *array, unsigned int *working, const size_t n) {
    unsigned int *original = array;
    unsigned int counts[BASE];

    // current shift and mask
    unsigned int shift = 0, mask = BASE - 1;

    // loop over all radices
    for ( ; mask; shift += POWER, mask <<= POWER) {
        // initialise counts
        // zero counts first
        memset(counts, 0, BASE * sizeof(*counts));
        for (size_t i = 0; i < n; i++) {
            // digit = (array[i] & mask) >> shift;
            counts[(array[i] & mask) >> shift]++;
        }

        // turn counts to prefix sums
        for (size_t i = 1; i < BASE; i++) {
            counts[i] += counts[i - 1];
        }

        // sort array into buckets
        // iteration starts at (n - 1)
        for (size_t i = n; i--; ) {
            // digit = (array[i] & mask) >> shift;
            // move array[i] into place based on counts[digit] - 1
            // subtracting 1 from counts first
            working[--counts[(array[i] & mask) >> shift]] = array[i];
        }

        swapp(&array, &working);
    }

    if (array != original) {
        // working is the "actual" array
        // so we copy "array" into "working"
        memcpy(working, array, n * sizeof(*array));
    }
}
