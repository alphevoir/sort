#include <stdio.h>

#include "common.h"

// prototypes
static size_t modulus(const int a, const size_t n);
static size_t binary_search_go(const size_t offset, const unsigned int x,
                               const unsigned int *array, const size_t n);

// functions
static size_t modulus(const int a, const size_t n) {
    size_t mod = a % n;
    return mod < 0 ? mod + n : mod;
}

size_t min(size_t x, size_t y) {
    return x < y ? x : y;
}

size_t max(size_t x, size_t y) {
    return x > y ? x : y;
}

void swap(unsigned int *x, unsigned int *y) {
    unsigned int t = *x;
    *x = *y;
    *y = t;
}

void swapp(unsigned int **x, unsigned int **y) {
    unsigned int *t = *x;
    *x = *y;
    *y = t;
}

// rotate by rot
void rotate(const int rot, unsigned int *array, const size_t n) {
    if (n == 0) {
        return;
    }

    // save last element
    unsigned int t = array[modulus(rot * (n - 1), n)];

    // don't set i = 0 since we already saved it in t
    for (size_t i = n - 1; i > 0; i--) {
        array[modulus(rot * i, n)] = array[modulus(rot * (i - 1), n)];
    }

    array[0] = t;
}

// rotate right 1
// more efficient than rotate
void rotate1(unsigned int *array, const size_t n) {
    if (n <= 0) {
        return;
    }

    // save last element
    unsigned int t = array[n - 1];

    // don't set i = 0 since we already saved it in t
    for (size_t i = n - 1; i > 0; i--) {
        array[i] = array[i - 1];
    }

    array[0] = t;
}

size_t binary_search(const unsigned int x, const unsigned int *array, const size_t n) {
    return binary_search_go(0, x, array, n);
}

static size_t binary_search_go(const size_t offset, const unsigned int x,
                               const unsigned int *array, const size_t n) {
    if (n == 0) {
        return offset;
    }

    size_t mid = n / 2;

    if (x == array[mid]) {
        return offset + mid;
    } else if (x < array[mid]) {
        return binary_search_go(offset, x, &array[0], mid);
    } else { // if (x > array[mid]) {
        return binary_search_go(offset + mid + 1, x, &array[mid + 1], n - (mid + 1));
    }
}

// show
void print_array(const char* prefix, const unsigned int *array, const size_t n) {
    for(size_t i = 0; i < n; ) {
        printf("%s", prefix == NULL ? "" : prefix);

        for (size_t j = 0; (i < n) && (j < 16); i++, j++) {
            printf("%s%4u", j ? " " : "", array[i]);
        }

        printf("\n");
    }
}
