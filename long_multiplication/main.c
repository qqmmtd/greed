#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEN     (128)
#define MAX_BASE    (16)
#define DEF_BASE    (10)


static int ctoi(const char c)
{
    if (('0' <= c) && (c <= '9')) {
        return c - '0';
    } else if (('a' <= c) && (c <= 'f')) {
        return c - 'a' + 10;
    } else if (('A' <= c) && (c <= 'F')) {
        return c - 'A' + 10;
    }
    return -1;
}

static void dump(const uint8_t x[], int xl)
{
    fprintf(stdout, "%d:", xl);
    for (int i = xl - 1; i >= 0; --i) {
        fprintf(stdout, "%x", x[i]);
    }
    fprintf(stdout, "\n");
}

static int calc(const uint8_t x[], int xl, const uint8_t y[], int yl,
        int base, uint8_t z[])
{
    for (int xi = 0; xi < xl; ++xi) {
        for (int yi = 0; yi < yl; ++yi) {
            int tmp = x[xi] * y[yi] + z[xi + yi];
            z[xi + yi] = tmp % base;
            z[xi + yi + 1] += tmp / base;
        }
    }
    // for (int zi = 0, quotient = 0; zi < xl + yl; ++zi) {
    //     int tmp = z[zi] + quotient;
    //     z[zi] = tmp % base;
    //     quotient = tmp / base;
    // }

    int zl;
    for (zl = xl + yl - 1; z[zl] == 0; --zl);

    return zl + 1;
}

static void usage()
{
    fprintf(stderr, "\n\
usage:\n\
    long_multiplication x y [base]\n\
");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int base = DEF_BASE;
    uint8_t x[MAX_LEN] = { 0, }, y[MAX_LEN] = { 0, }, z[MAX_LEN * 2] = { 0, };
    int xl, yl, zl;

    switch (argc) {
    case 4:
        base = atoi(argv[3]);
        assert((base > 1) && (base <= MAX_BASE));
    case 3:
        xl = strlen(argv[1]);
        assert(xl <= MAX_LEN);
        for (int i = 0; i < xl; ++i) {
            x[i] = ctoi(argv[1][xl - 1 - i]);
            assert(x[i] < base);
        }
        dump(x, xl);
        yl = strlen(argv[2]);
        assert(yl <= MAX_LEN);
        for (int i = 0; i < yl; ++i) {
            y[i] = ctoi(argv[2][yl - 1 - i]);
            assert(x[i] < base);
        }
        dump(y, yl);
        break;
    default:
        usage();
    }

    if ((zl = calc(x, xl, y, yl, base, z)) < 0) {
        fprintf(stderr, "calc failed\n");
        return EXIT_FAILURE;
    }

    dump(z, zl);

    return EXIT_SUCCESS;
}
