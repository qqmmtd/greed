#include <string.h>

#include "base64.h"

static void usage(const char *prog)
{
    fprintf(stderr, "base64 infile\n");
    fprintf(stderr, "base64 -d infile outfile\n");
}

int main(int argc, char *argv[])
{
    int rc = 0;
    FILE *in, *out;

    if (argc == 2) {
        in = fopen(argv[1], "rb");
        rc = encode(in, stdout);
        fclose(in);
    } else if ((argc == 4) && !strcmp(argv[1], "-d")) {
        in = fopen(argv[2], "r");
        out = fopen(argv[3], "wb");
        rc = decode(in, out);
        fclose(in);
        fclose(out);
    } else {
        usage(argv[0]);
    }

    return rc;
}
