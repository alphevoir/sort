#ifndef RADIX
#define RADIX

#define POWER 4
#define BASE  (1 << POWER)

void radix(unsigned int *array, const size_t n);

#endif // RADIX
