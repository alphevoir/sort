#include <stdio.h>

#include "common.h"
#include "insertion.h"
#include "quick.h"

static void partition(unsigned int *array, const size_t n, size_t *l, size_t *r);

void quick(unsigned int *array, const size_t n) {
    // if (n <= 1) {
    //     return;
    // } else if (n == 2) {
    //     if (array[0] > array[1]) {
    //         swap(&array[0], &array[1]);
    //     }
    //     return;
    // }

    if (n <= 16) {
        insertion(array, n);
        return;
    }

    size_t l, r;
    partition(array, n, &l, &r);

    quick(&array[0], l);
    quick(&array[r + 1], n - (r + 1));
}

static void partition(unsigned int *array, const size_t n, size_t *l, size_t *r) {
    size_t mid = n / 2;

    // want lo < mid < hi
    // lo < hi
    if (array[0] > array[n - 1]) {
        swap(&array[0], &array[n - 1]);
    }

    // lo < mid
    if (array[0] > array[mid]) {
        swap(&array[0], &array[mid]);
    }

    // mid < hi
    if (array[mid] > array[n - 1]) {
        swap(&array[mid], &array[n - 1]);
    }

    unsigned int pivot = array[mid];

    size_t left = 0, middle = 0, right = n - 1;

    while (middle <= right) {
        if (array[middle] < pivot) {
            // increase left side
            swap(&array[middle], &array[left]);
            left++; middle++;
        } else if (array[right] > pivot) {
            // no swap necessary
            right--;
        } else if (array[middle] > pivot) {
            // increase right side
            swap(&array[middle], &array[right]);
            right--;
        } else { // if (array[middle] == pivot)
            // increase middle
            middle++;
        }
    }

    *l = left;
    *r = right;
}
