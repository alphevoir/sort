#include <stdio.h>

#include "common.h"
#include "shell.h"

void shell(unsigned int *array, const size_t n) {
    static const size_t gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    static const size_t gaps_n = 8;

    // iterate through all gaps
    for (size_t k = 0; k < gaps_n; k++) {
        size_t gap = gaps[k];

        // start at array[gap]
        // sort array[gap:n] by gaps using insertion sort
        for (size_t i = gap; i < n; i++) {
            // store current index
            unsigned int t = array[i];
            size_t j = i;

            // shuffle everything up
            // (j - gap) >= 0 *explicit*
            for ( ; (j >= gap) && (array[j - gap] > t); j -= gap) {
                array[j] = array[j - gap];
            }

            // move original element into sorted position
            array[j] = t;
        }
    }
}
