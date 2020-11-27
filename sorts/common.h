#ifndef COMMON
#define COMMON

size_t min(size_t x, size_t y);
size_t max(size_t x, size_t y);

void swap(unsigned int *x, unsigned int *y);
void swapp(unsigned int **x, unsigned int **y);
void rotate(const int rot, unsigned int *array, const size_t n);
void rotate1(unsigned int *array, const size_t n);
size_t binary_search(const unsigned int x, const unsigned int *array, const size_t n);
void print_array(const char* prefix, const unsigned int *array, const size_t n);

#endif // COMMON
