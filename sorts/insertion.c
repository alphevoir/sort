#include <stdio.h>

#include "common.h"
#include "insertion.h"

void insertion(unsigned int *array, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        // store current index
        unsigned int t = array[i];
        size_t j = i;

        // shuffle everything up
        // (j - 1) >= 0 *explicit*
        for ( ; (j >= 1) && (array[j - 1] > t); j--) {
            array[j] = array[j - 1];
        }

        // move original element into sorted position
        array[j] = t;
    }
}

void insertion_smart(unsigned int *array, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        size_t j = binary_search(array[i], array, i);

        // off by 1 error
        rotate1(&array[j], i - j + 1);
    }
}
