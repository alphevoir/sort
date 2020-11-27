#include <stdio.h>

#include "common.h"
#include "bubble.h"

void bubble(unsigned int *array, const size_t n) {
    size_t m = (size_t) n;

    // array is sorted if last swap occured betwee array[0] and array[1]
    // don't need do while because m always starts > 1
    // if array has more than 1 elemnt
    while (m > 1) {
        size_t i_last = 0;

        for (size_t i = 1; i < m; i++) {
            if (array[i - 1] > array[i]) {
                swap(&array[i - 1], &array[i]);
                i_last = i;
            }
        }

        // remember last swap
        m = i_last;
    }
}
