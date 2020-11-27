#include <stdio.h>

#include "common.h"
#include "selection.h"

void selection(unsigned int *array, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        size_t min = i;

        for (size_t j = i; j < n; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }

        swap(&array[min], &array[i]);
    }
}
