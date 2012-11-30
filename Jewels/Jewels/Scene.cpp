/* 
 * Scene.cpp 
 * CPE 471, Computer Graphics 
 * @author Gagandeep Singh Kohli
 **/

#include "Scene.h"
#include "JewelsModel.h"
#include "JewelsController.h"

int winWidth, winHeight; 
 
float angle = 0.0, axis[3], trans[3]; 
bool trackballEnabled = true; 
bool trackballMove = false; 
bool trackingMouse = false; 
bool redrawContinue = false; 
bool zoomState = false; 
bool shiftState = false; 

//transform matrix
GLfloat transformMatrix[16] = {1,0,0,0,
	                           0,1,0,0,
							   0,0,1,0,
							   0,0,0,1};



GLfloat lightXform[4][4] = { 
   {1.0, 0.0, 0.0, 0.0}, 
   {0.0, 1.0, 0.0, 0.0}, 
   {0.0, 0.0, 1.0, 0.0}, 
   {0.0, 0.0, 0.0, 1.0} 
}; 
 
GLfloat objectXform[4][4] = { 
   {1.0, 0.0, 0.0, 0.0}, 
   {0.0, 1.0, 0.0, 0.0}, 
   {0.0, 0.0, 1.0, 0.0}, 
   {0.0, 0.0, 0.0, 1.0} 
}; 
 
GLfloat *trackballXform = (GLfloat *)objectXform; 

// initial viewer position 
static GLdouble modelTrans[] = {0.0, 0.0, -5.0}; 
// initial model angle 
static GLfloat theta[] = {0.0, 0.0, 0.0}; 
static float thetaIncr = 5.0; 
 
// animation transform variables 
static GLdouble translate[3] = {-10.0, 0.0, 0.0}; 
 
static GLfloat currentTrans[3] = {0.0, 0.0, 0.0}; 
 
// queue<pair<int,int>> mouseClicks = queue<pair<int,int>>();
 GLfloat diffuseBlue[] = {0.0, 0.0, 1.0, 1.0};
 GLfloat diffuseGreen1[] = {0.2, 0.8, 0.2, 1.0};
 GLfloat diffuseYellow[] = {1.0, 0.0, 1.0, 1.0};
 GLfloat diffuseRed[] = {1.0, 0.0, 0.0, 1.0};

 const int totalPieces = 4;
 const int boardSize = 8;
 const int similarAdjTileLimit = 2;

 GLfloat* colors[] = {diffuseBlue, 
                      diffuseGreen1,
                      diffuseYellow,
                      diffuseRed}; 

JewelsModel jewelsModel = JewelsModel(totalPieces, boardSize, similarAdjTileLimit);
JewelsController jewelsController = JewelsController(&jewelsModel);
//--------------------------------------------------------- 
//   Set up the view 
 
void setUpView() { 
   // this code initializes the viewing transform 
   glLoadIdentity(); 
 
   // moves viewer along coordinate axes 
   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
 
   // move the view back some relative to viewer[] position 
   glTranslatef(0.0f,0.0f, 0.0f); 
 
   // rotates view 
   glRotatef(0, 1.0, 0.0, 0.0); 
   glRotatef(0, 0.0, 1.0, 0.0); 
   glRotatef(0, 0.0, 0.0, 1.0); 
 
   return; 
} 
 
//---------------------------------------------------------- 
//  Set up model transform 
 
void setUpModelTransform() { 
 
   // moves model along coordinate axes 
   glTranslatef(modelTrans[0], modelTrans[1], modelTrans[2]); 
 
   // rotates model 
   glRotatef(theta[0], 1.0, 0.0, 0.0); 
   glRotatef(theta[1], 0.0, 1.0, 0.0); 
   glRotatef(theta[2], 0.0, 0.0, 1.0); 
 
 
} 
 
//---------------------------------------------------------- 
//  Set up the light 
 
void setUpLight() { 
   // set up the light sources for the scene 
   // a directional light source from directly behind 
   GLfloat lightDir[] = {0.0, 0.0, 5.0, 0.0}; 
   GLfloat diffuseComp[] = {1.0, 1.0, 1.0, 1.0}; 
 
   glEnable(GL_LIGHTING); 
   glEnable(GL_LIGHT0); 
 
   glLightfv(GL_LIGHT0, GL_POSITION, lightDir); 
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseComp); 
 
   return; 
} 
 
//----------------------------------------------------------- 
//  Callback functions 
 
void reshapeCallback(int w, int h) { 
 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity();
   setUpProjection(w, h);
} 
 
float lastPos[3] = {0.0, 0.0, 0.0}; 
int curx, cury; 
int startX, startY; 
 
void trackball_ptov(int x, int y, int width, int height, float v[3]) { 
   float d, a; 
   // project x, y onto a fractal centered within width, height 
   v[0] = (2.0*x - width) / width; 
   v[1] = (height - 2.0*y) / height; 
   d = (float) sqrt(v[0]*v[0] + v[1]*v[1]); 
   v[2] = (float) cos((3.14159/2.0) * ((d<1.0)? d : 1.0)); 
   a = 1.0 / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); 
   v[0] *= a; 
   v[1] *= a; 
   v[2] *= a; 
} 
 
void mouseMotion(int x, int y) { 
   float curPos[3], dx, dy, dz; 
 
   if (zoomState == false && shiftState == false) { 
 
      trackball_ptov(x, y, winWidth, winHeight, curPos); 
 
      dx = curPos[0] - lastPos[0]; 
      dy = curPos[1] - lastPos[1]; 
      dz = curPos[2] - lastPos[2]; 
 
      if (dx||dy||dz) { 
         angle = 90.0 * sqrt(dx*dx + dy*dy + dz*dz); 
 
         axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1]; 
         axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2]; 
         axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0]; 
 
         lastPos[0] = curPos[0]; 
         lastPos[1] = curPos[1]; 
         lastPos[2] = curPos[2]; 
      } 
 
   } 
   else if (zoomState == true) { 
      curPos[1] = y; 
      dy = curPos[1] - lastPos[1]; 
 
      if (dy) { 
         modelTrans[2] += dy * 0.01; 
         lastPos[1] = curPos[1]; 
      } 
   } 
   else if (shiftState == true) { 
      curPos[0] = x;  
      curPos[1] = y; 
      dx = curPos[0] - lastPos[0]; 
      dy = curPos[1] - lastPos[1]; 
 
      if (dx) { 
         modelTrans[0] += dx * 0.01; 
         lastPos[0] = curPos[0]; 
      } 
      if (dy) { 
         modelTrans[1] -= dy * 0.01; 
         lastPos[1] = curPos[1]; 
      } 
   } 
   glutPostRedisplay( ); 
 
} 
 
void startMotion(long time, int button, int x, int y) { 
   if (!trackballEnabled) return; 
 
   trackingMouse = true; 
   redrawContinue = false; 
   startX = x; startY = y; 
   curx = x; cury = y; 
   trackball_ptov(x, y, winWidth, winHeight, lastPos); 
   trackballMove = true; 
} 
 
void stopMotion(long time, int button, int x, int y) { 
   if (!trackballEnabled) return; 
    
   trackingMouse = false; 
 
   if (startX != x || startY != y) 
      redrawContinue = true; 
   else { 
      angle = 0.0; 
      redrawContinue = false; 
      trackballMove = false; 
   } 
} 
 

void mouseCallback(int button, int state, int x, int y) { 
  int w, h;
 
  if ( (button == GLUT_LEFT_BUTTON) &&
       (state == GLUT_DOWN)) {
    
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];
    
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    glSelectBuffer(BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);
    
    glInitNames();
    glPushName(0);
    
    glPushMatrix();
      //now "render" everything for selection
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPickMatrix((GLdouble)x, (GLdouble) (viewport[3] - y),
                     5.0, 5.0, viewport);
      w = viewport[2];
      h = viewport[3];
      setUpProjection(w, h);

      //the rest is the same as display(), except the mode flag is different (GL_SELECT)
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      setUpView();
      setUpModelTransform();
      drawObjs(GL_SELECT);
     glPopMatrix();

     glFlush();

     hits = glRenderMode(GL_RENDER);
     processHits(hits, selectBuf);

     // re-render everything again for display
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     setUpProjection(w, h);
  };
  display();    
} 
       
void keyCallback(unsigned char key, int x, int y) { 
      // move viewer with x, y, and z keys
   // capital moves in + direction, lower-case - direction
   if (key == 'x') modelTrans[0] -= 1.0;
   if (key == 'X') modelTrans[0] += 1.0;
   if (key == 'y') modelTrans[1] -= 1.0;
   if (key == 'Y') modelTrans[1] += 1.0;
   if (key == 'z') modelTrans[2] -= 1.0;
   if (key == 'Z') modelTrans[2] += 1.0;
   if (key == 'r') {
      theta[0] = 0.0; theta[1] = 0.0; theta[2] = 0.0;
   }
   if (key == '-') {
      thetaIncr = -thetaIncr;
   }
   if (key == '+') {
      if (thetaIncr < 0) thetaIncr = thetaIncr - 1.0;
      else               thetaIncr = thetaIncr + 1.0;
   }
    // rotate camera
   if (key == '<') {
      theta[1] += thetaIncr;
      if (theta[1] > 360.0) theta[1] -= 360.0;
   }

   if (key == '>') {
      theta[1] -= thetaIncr;
      if (theta[1] < 0) theta[1] = 360.0;
   }

   display();
   glutPostRedisplay();

} 

//---------------------------------------------------------
//   Set up the projection

void setUpProjection(int w, int h) {
   // this code initializes the projection transform
   glViewport(0,0,w,h);

   if (w < h) {
      glFrustum(-2.0, 2.0, -2.0*(GLfloat) h / (GLfloat) w,
                2.0*(GLfloat) h / (GLfloat) w, 2.0, 200.0);
   }
   else {
      glFrustum(-2.0, 2.0, -2.0*(GLfloat) w / (GLfloat) h,
                2.0*(GLfloat) w / (GLfloat) h, 2.0, 200.0);
   }

   glMatrixMode(GL_MODELVIEW);

   return;
}

void processHits(GLint hits, GLuint buffer[])
{
   // this function goes through the selection hit list of object names

   int i, j;
   GLuint *ptr;
   GLuint *nearest = NULL;

  
   //printf("hits = %d\n", hits);
   if (hits==0){
   //  printf("You have not selected any object.\n");
     return;
   };
   ptr = (GLuint *) buffer;
   nearest = (GLuint *) buffer;
   for(i=0; i<hits; i++) {
   if ( *(nearest+1) > *(ptr+1)) nearest = ptr ;
      ptr++;
      //printf("  front at %g\n", (float) *ptr/0x7fffffff);
      
      ptr++;
      //printf("  back at = %g\n",(float) *ptr/0x7fffffff);
      ptr++;
      ptr++;
   }

   if ( hits > 0 ) {
     int name = *(nearest + 3);
     int row = name / boardSize;
     int col = name % boardSize;
    // printf ("You have selected piece %d %d\n", row, col);
     handleClick(row, col);
   };
   //printf("**************************************************************\n");
}

void handleClick(int row, int col) {
  jewelsController.handleClick(row, col);
};
 
//--------------------------------------------------------- 
//  Main routines 
 
void display (void) { 
   // this code executes whenever the window is redrawn (when opened, 
   //   moved, resized, etc. 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
   // set the viewing transform 
   setUpView(); 
 
   // set up light source 
   setUpLight(); 
 
   // start drawing objects 
   setUpModelTransform(); 
 
   if (trackballMove) { 
      glPushMatrix(); 
      glLoadIdentity(); 
      glRotatef(angle, axis[0], axis[1], axis[2]); 
      glMultMatrixf((GLfloat *) trackballXform); 
      glGetFloatv(GL_MODELVIEW_MATRIX, trackballXform); 
      glPopMatrix(); 
   } 
   glPushMatrix(); 
   glMultMatrixf((GLfloat *) objectXform); 
   drawObjs(GL_RENDER); 
   glPopMatrix(); 
 
   glutSwapBuffers(); 
} 

void drawObjs(GLenum mode){
	// save the transformation state
  glPushMatrix();
    int ** board = jewelsModel.getBoard();
    float totalXSpace =  (2 * totalPieces - 1) / 2.0;
    //center the board
    glTranslatef(-totalXSpace, totalXSpace, 0);
    glPushMatrix();

      for (int row = 0; row < boardSize; row++) {
        glPushMatrix();
          for (int col = 0; col < boardSize; col++) {
            int color = board[row][col];
            glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[color]);
            int name = (row * boardSize) + col;
            if (mode == GL_SELECT) glLoadName(name);
            drawJewel();
            glTranslatef(1, 0, 0);  
          }
        glPopMatrix();
        glTranslatef(0, -1, 0);
      }
      
    glPopMatrix();
    glTranslatef(-8, -8, 2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
   glLoadName(5);
   glScalef(0.002, 0.002,0.002);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');  
  glPopMatrix();
  
 // glRasterPos2d(0, 0);
  //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'd');
  
}; 

void jewels3d(GLenum mode){
	// save the transformation state
  glPushMatrix();
    int ** board = jewelsModel.getBoard();
    float totalXSpace =  (2 * totalPieces - 1) / 2.0;
    //center the board
    glTranslatef(-totalXSpace, totalXSpace, 0);
    glPushMatrix();
    int quad = boardSize / 4;
    int rotate = 0;
      for (int row = 0; row < boardSize; row++) {
        glPushMatrix();
        int rotate = boardSize / 4;
          for (int col = 0; col < boardSize; col++) {
            int color = board[row][col];
            glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[color]);
            int name = (row * boardSize) + col;
            if (mode == GL_SELECT) glLoadName(name);
            drawJewel();
            if (col < rotate)
              glTranslatef(1, 0, 0);
            else if(col < 2*rotate) 
              glTranslatef(0, 0, -1);
            else if (col < 3*rotate) 
              glTranslatef(-1, 0, 0);
            else   
              glTranslatef(0, 0, 1);
          }
        glPopMatrix();
        glTranslatef(0, -1, 0);
      }
    glPopMatrix();
  glPopMatrix();
};

void drawCone(){
  glPushMatrix();
    glRotatef(-90, 1, 0 ,0);
    glutSolidCone(2, 2, 36, 36);
  glPopMatrix();
};

void drawJewel(){
  glPushMatrix();
    glutSolidSphere(.5, 4, 4);
  glPopMatrix();
};

void init(int argc, char* argv[]) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("Jewels"); 
	glEnable(GL_DEPTH_TEST); 
	glutDisplayFunc(display); 
    glutReshapeFunc(reshapeCallback); 
    glutKeyboardFunc(keyCallback); 
    glutMouseFunc(mouseCallback); 
    glutMotionFunc(mouseMotion); 
	glutMainLoop(); 
}
 
