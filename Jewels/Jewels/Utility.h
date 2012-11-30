#ifndef UTILITY
#define UTILITY


// some function prototypes 
 
void normalize(float[3]); 
void normCrossProd(float[3], float[3], float[3]); 
void computeNormal(float *origin, float *d1, float *d2, float *normal);
float dotProduct(float[3],float[3]);
#endif