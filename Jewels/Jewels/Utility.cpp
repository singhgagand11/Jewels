#include <stdio.h> 
#include <math.h>
#include "Utility.h"

//--------------------------------------------------------- 
//  Utility functions 
 
void normalize(float v[3]) { 
   // normalize v[] and return the result in v[] 
   // from OpenGL Programming Guide, p. 58 
   float d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); 
   if (d == 0.0) { 
      printf("zero length vector"); 
      return; 
   } 
   v[0] = v[0]/d; v[1] = v[1]/d; v[2] = v[2]/d; 
} 
 
void normCrossProd(float v1[3], float v2[3], float out[3]) { 
   // cross v1[] and v2[] and return the result in out[] 
   // from OpenGL Programming Guide, p. 58 
   out[0] = v1[1]*v2[2] - v1[2]*v2[1]; 
   out[1] = v1[2]*v2[0] - v1[0]*v2[2]; 
   out[2] = v1[0]*v2[1] - v1[1]*v2[0]; 
   normalize(out); 
} 

void computeNormal(float *origin, float *d1, float *d2, float *normal){
  float vector1[3],  vector2[3];
  for(int i =0; i < 3; i++){
    vector1[i] = d1[i] - origin[i];
    vector2[i] = d2[i] - origin[i];
  }
  normCrossProd(d1, d2, normal);
}

float dotProduct(float v1[3], float v2[3])
{
    float result = 0;
    for (int index = 0; index < 3; index++) {

       result += v1[index] * v2[index];
    } 

    return result;
};
