#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "common.h"
#include "merge.h"

static void merge_arrays(unsigned int *array, unsigned int *dest,
                         const size_t left, const size_t right, const size_t end);
static void mergesort(unsigned int *array, unsigned int *working, const size_t n);

void merge(unsigned int *array, const size_t n) {
    unsigned int *working;

    working = (unsigned int *) malloc(n * sizeof(*working));
    assert(working != NULL);

    mergesort(array, working, n);
    free(working);
}

static void merge_arrays(unsigned int *array, unsigned int *dest,
                         const size_t left, const size_t right, const size_t end) {
    size_t l = left, r = right;

    // copy slice left:end
    for (size_t i = left; i < end; i++) {
        // if there are still elements in the left list (l < right)
        // and if left < right
        if ((l < right) &&
            ((r >= end) || (array[l] < array[r]))) {
            // insert left
            dest[i] = array[l];
            l++;
        } else {
            // insert right
            dest[i] = array[r];
            r++;
        }
    }
}

static void mergesort(unsigned int *array, unsigned int *working, const size_t n) {
    unsigned int *original = array;

    for (size_t width = 1; width < n; width *= 2) {
        for (size_t i = 0; i < n; i += 2 * width) {
            merge_arrays(array, working, i, min(i + width, n), min(i + 2 * width, n));
        }

        // switch array pointers
        swapp(&array, &working);
    }

    if (array != original) {
        // working is the "actual" array
        // so we copy "array" into "working"
        memcpy(working, array, n * sizeof(*array));
    }
}
