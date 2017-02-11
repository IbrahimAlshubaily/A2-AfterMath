#include "vectors.h"

vector vector_init(float x, float y, float z){
 vector v;
 v.x=x;
 v.y=y;
 v.z=z;
 v.length=sqrt(x*x+y*y+z*z);
	return v;
}

vector vector_add(vector v1, vector v2){
	return vector_init(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
}
	
float vector_dot(vector v1, vector v2){
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z ;
}
	
int vector_normalize(vector *v){
	if(!v->length) return 1;
	v->x/=v->length;
	v->y/=v->length;
	v->z/=v->length;
	v->length=1;	
	return 0;
}	
void vector_print(vector v){
	printf("x=%f\ny=%f\nz=%f\nlength=%f\n",v.x,v.y,v.z,v.length);
}	
