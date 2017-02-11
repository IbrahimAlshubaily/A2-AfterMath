//Ibrahim Alshubaily
#include "vectors.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *joinrev(char a[], char *b);
void *joinrev_generic(void * a, void * b, int elementSize, int aSize, int bSize);
int readTextAddBinary(char * input, char * output);
int readBinaryNormText(char * input, char * output);
int readNormTextWriteNormBinary(char * input, char * output);
int wc(char * input);
