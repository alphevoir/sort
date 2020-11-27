#include <stdio.h>

#include "common.h"
#include "heap.h"

static void heapify(unsigned int *array, const size_t n);
static void sift_down(unsigned int *array, const size_t i, const size_t n);

void heap(unsigned int *array, const size_t n) {
    // convert to heap
    heapify(array, n);

    // iteration starts at (n - 1)
    for (size_t i = n; i--; ) {
        // swap largest element (root of max heap) into place
        swap(&array[0], &array[i]);
        // repair heap excluding last element
        sift_down(array, 0, i);
    }
}

static void heapify(unsigned int *array, const size_t n) {
    // the last n/2 nodes do not have children
    // iteration starts at (n/2 - 1)
    for (size_t i = n / 2; i--; ) {
        sift_down(array, i, n);
    }
}

static void sift_down(unsigned int *array, const size_t i, const size_t n) {
    size_t child, left = 2 * i + 1, right = 2 * i + 2;

    // check within range
    if (left < n) {
        // we want to swap with the largest child
        if ((right < n) && (array[right] > array[left])) {
            child = right;
        } else {
            child = left;
        }

        // swap if root larger than child
        if (array[i] < array[child]) {
            swap(&array[i], &array[child]);
            // continue repairing heap
            sift_down(array, child, n);
        }
    }
}
