#include "base64.h"

static const char *map =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int encode(FILE *in, FILE *out)
{
    unsigned char buf[3], b[4];
    size_t rsize;

    if (!in || !out) {
        return -1;
    }

    while ((rsize = fread((void *) buf, 1, 3, in)) > 0) {
        if (rsize == 1) {
            buf[rsize] = 0;
            buf[rsize + 1] = 0;
        } else if (rsize == 2) {
            buf[rsize] = 0;
        }
        b[0] = buf[0] >> 2;
        b[1] = ((buf[0] & 0x03) << 4) | (buf[1] >> 4);
        b[2] = ((buf[1] & 0x0F) << 2) | (buf[2] >> 6);
        b[3] = buf[2] & 0x3F;
        fputc(map[b[0]], out);
        fputc(map[b[1]], out);
        if (rsize == 3) {
            fputc(map[b[2]], out);
            fputc(map[b[3]], out);
        } else if (rsize == 2) {
            fputc(map[b[2]], out);
            fputc('=', out);
        } else /* if (rsize == 1) */ {
            fputc('=', out);
            fputc('=', out);
        }
    }

    return 0;
}

int decode(FILE *in, FILE *out)
{
    unsigned char map2[256], buf[4], d[3], i, m3;
    size_t rsize;

    if (!in || !out) {
        return -1;
    }

    for (i = 0; i < 64; ++i) {
        map2[map[i]] = i;
    }

    while ((rsize = fread((void *) buf, 1, 4, in)) == 4) {
        if (buf[2] == '=') {
            m3 = 1;
        } else if (buf[3] == '=') {
            m3 = 2;
        } else {
            m3 = 3;
        }
        d[0] = (map2[buf[0]] << 2) | (map2[buf[1]] >> 4);
        d[1] = ((map2[buf[1]] & 0x0F) << 4) | (map2[buf[2]] >> 2);
        d[2] = ((map2[buf[2]] & 0x03) << 6) | map2[buf[3]];
        fwrite((void *) d, 1, m3, out);
    }

    return 0;
}