/**
 * Fractal.cpp
 * Implementation of Fractal object that was defined in 
 * Fractal.h
 * @author Gagandeep Singh Kohli
 */
#ifndef FRACTAL 
#include "Fractal.h"
#endif

#include <math.h>
#include <iostream>

using namespace std;

Fractal::Fractal(float ruggedness, int depth, int length) {
  maxHeight = 0;
  minHeight = 0;
  //call the helper function for generating the points
  initVertices(depth); 
  createFractal(ruggedness, depth, length);
};

int Fractal::getIteration() {
  return iteration;
}
void Fractal::initVertices(int depth) {
  
   iteration = (int) pow(2.0, (double)depth) + 1;
   int colSize = iteration;
   for (int row = 0; row < colSize; row++) {
     
     vector<vector<float> > rowVertices;
       for (int col = 0; col < colSize; col++) {
         vector<float> coord;
         rowVertices.push_back(coord);
       }
      vertices.push_back(rowVertices);
   }

    
   vector<float> *v1 = &vertices.at(0).at(0);
   (*v1).push_back(0);
   vector<float> *v2 = &vertices.at(0).at(colSize -1);
   (*v2).push_back(0);
   
   vector<float> *v3 = &vertices.at(colSize-1).at(0);
   (*v3).push_back(0);
   vector<float> *v4 = &vertices.at(colSize-1).at(colSize-1);
   (*v4).push_back(0);
   


};

const vector<vector<vector<float> > > Fractal::getVertices()
{
  //return a constant list of the vertices
  return vertices;
};

void Fractal::createFractal(float ruggedness, int depth, int length) {
  int max = (int) pow(2.0, depth) ;
 recurse(0, max, 0, max, length, ruggedness, depth);
 insertXZ(length);
};

void Fractal::insertXZ(int sideLength) 
{
   //total size of longitude slices
   int longSize = vertices.size();
  
   //FOR each slice of longitude
   for(int longitude = 0; longitude < longSize; longitude++) {
     //get the top get of vertices
     vector<vector<float> > topVertices = vertices.at(longitude);

     float zCoord =  ((float) longitude / ((float) longSize - 1.0)) * sideLength;
     //total latitude slices
     int latSize = topVertices.size();
     //FOR each latitude slice connect the quads
     for(int latitude = 0; latitude < latSize; latitude++) {

      float xCoord = ((float) latitude / ((float) latSize - 1.0)) * sideLength;
      vector<float> * vec = &vertices.at(longitude).at(latitude);
      float yCoord = (*vec).back(); 

      if(yCoord > maxHeight)
        maxHeight = yCoord;
      if(yCoord < minHeight)
        minHeight = yCoord;

      (*vec).pop_back();

      (*vec).push_back(xCoord);
      (*vec).push_back(yCoord);
      (*vec).push_back(zCoord);
     }
   }
};

void Fractal::recurse(int xMin, int xMax, int zMin, int zMax, 
                      int sideLength, float R, int depth)
{
  if(depth == 0)
    return;
  int xMid = (xMin + xMax) / 2;
  int zMid = (zMin + zMax) / 2;
  
  float yTopLeftCoord = vertices.at(zMin).at(xMin).front();
  float yTopRightCoord = vertices.at(zMin).at(xMax).front();
  float yBottomLeftCoord = vertices.at(zMax).at(xMin).front();
  float yBottomRightCoord = vertices.at(zMax).at(xMax).front();

  
  //if top mid is empty
  if (vertices.at(zMin).at(xMid).empty())
  {
    setYValue(yTopLeftCoord, yTopRightCoord, xMid, zMin, R);
  }

  //if bottom mid is empty
  if (vertices.at(zMax).at(xMid).empty())
  {
    setYValue(yBottomLeftCoord, yBottomRightCoord, xMid, zMax, R);
  }

  //if left mid is empty
  if (vertices.at(zMid).at(xMin).empty())
  {
    setYValue(yTopLeftCoord, yBottomLeftCoord, xMin, zMid, R);
  }

  //if right mid is empty
  if (vertices.at(zMid).at(xMax).empty())
  {
    setYValue(yTopRightCoord, yBottomRightCoord, xMax, zMid, R);
  }

  //if center is empty
  if (vertices.at(zMid).at(xMid).empty()){
    float yMidLeft = vertices.at(zMid).at(xMin).front();
    float yMidRight = vertices.at(zMid).at(xMax).front();
    setYValue(yMidLeft, yMidRight, xMid, zMid, R);
  }
  
    
    recurse(xMin, xMid, zMin, zMid, sideLength/2, R/2.0, depth-1);
    recurse(xMid, xMax, zMin, zMid, sideLength/2, R/2.0, depth-1);
    recurse(xMin, xMid, zMid, zMax, sideLength/2, R/2.0, depth-1);
    recurse(xMid, xMax, zMid, zMax, sideLength/2, R/2.0, depth-1);
 
  
};

float Fractal::setYValue(float yNot, float yOne, int x, int z, float R) {
    float y = ( yNot + yOne ) / 2.0;
    float ran = ((((float)rand() / (float)RAND_MAX) * 2.0) - 1.0) * R;
    y += ran;

    //set the midpoint
    vertices.at(z).at(x).push_back(y);

    return y;
};

float Fractal::getMaxHeight(){
  return maxHeight;
};

float Fractal::getMinHeight(){
  return minHeight;
};