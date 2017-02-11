#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	float x;
	float y;
	float z;
	float length;
} vector;

vector vector_init(float x, float y, float z);
vector vector_add(vector v1, vector v2);
float vector_dot(vector v1, vector v2);
int vector_normalize(vector *v);
void vector_print(vector v);
