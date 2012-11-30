/**
 * Fractal.h
 * A sphere library class that generates a sphere based on the number
 * of slices to subdivide the sphere into longitude and latitude.
 * It provides user an access to the vertices of the sphere.
 * 
 * @author Gagandeep Singh Kohli
 **/

/**
 * Fractal.h
 * A Header for Fractal object that increase a constructor
 * for creating a sphere by number of slices or stacks. 
 * And user has the ability to reterive the list of vertices.
 * @author Gagandeep Kohli
 */
#include <vector>
#include <list>
#include <array>
using namespace std;

//constant for PI 3.14
const float PI = 3.14f;

/**
 * Generates a sphere object for given number of slices, and 
 * provides a function to access the list of list of vertices
 * on the sphere. 
 **/
class Fractal {
  public:
  /**
   * Constructs a sphere.
   * @param slices the number of subdivision around the z axis
   * @param stacks the number of subdivision along the z axis
   */
  Fractal(float ruggedness, int depth, int length);
  /**
   * Returns the list of vertices generates for the sphere
   * the outer set of vector is list of stacks and inner
   * vector if list slices. The last set of vector includes
   * 3 items: x, y, z coordinates.
   * @return vector of vector of vector of vertices
   */
  const vector<vector<vector<float> > > getVertices();

  float getMaxHeight();

  float getMinHeight();

  int getIteration();

  private:
  //set of vertices for generating the sphere 
  vector<vector<vector<float> > > vertices;

  /**
   * Helper function for finding the slices and stacks of vertices
   * for the sphere.
   **/
  void createFractal(float ruggedness, int depth, int length);

  void recurse(int xMin, int xMax, int zMin, int zMax, int sideLength, float R, int depth);

  void initVertices(int depth);

  float setYValue(float yNot, float yOne, int x, int z, float R);

  void insertXZ(int sideLength);

  float maxHeight;

  float minHeight;

  int iteration;
};
