#ifndef __BASE64_H__
#define __BASE64_H__


#include <stdio.h>

int encode(FILE *in, FILE *out);
int decode(FILE *in, FILE *out);


#endif /* __BASE64_H__ */