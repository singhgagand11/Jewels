/**
 * Scene.h
 * Function prototypes for Scene class. These prototypes
 * set up the scene, mouse call back, motion tracking, 
 * lighting, model, view, and transformation.
 * ALL CALLS WERE IMPLEMENTED BY PROFESSOR BUCKALEW
 * @author Chris Buckalew
 * @author Gagandeep Singh Kohli added transformation
 **/
#ifndef SCENE
#define SCENE

#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <queue>
#include <iostream>
#include "JewelsModel.h"
#include "JewelsController.h"
#include "JewelsPiece.h"
#include <ctime>

using namespace std;


#ifndef UTILITY
#include "Utility.h"
#endif

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif


#define BUFSIZE 512

void display (void);
void mouseCallback(int button, int state, int x, int y);
void stopMotion(long time, int button, int x, int y);
void startMotion(long time, int button, int x, int y);
void trackball_ptov(int x, int y, int width, int height, float v[3]);
void reshapeCallback(int w, int h) ;
void setUpLight();
void setUpModelTransform();
void setUpView();
float* color(float slope);
void setUpProjection(int w, int h);
void processHits(GLint hits, GLuint buffer[]);
void handleClick(int row, int col);
void drawObjs(GLenum mode);
void drawCylinder();
void drawJewel();
void mouseMotion(int x, int y);
void keyCallback(unsigned char key, int x, int y);

/**
* initialize open gl scene and start rendering
* @param argc number of command line argument
* @param argv array of command line argument
**/
void init(int argc, char* argv[]);
void repaint(JewelsPiece ** board);
void animateRemove(int step);
#endif
