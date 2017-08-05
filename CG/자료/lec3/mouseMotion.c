//  Example: mouseMotion.c
//

#include<stdlib.h>
#include<gl\glut.h>

int winW, winH;   // <---- window's width (W) and height (H)

int mouseX=0, mouseY=0; // <-- use globals to know last mouse click location

// Track Window Dimensions
void reshape(int w, int h)
{
  winW = w;
  winH = h;
   
  glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
  glLoadIdentity();             // This clear any existing matrix
   
   gluOrtho2D (0, w, 0, h);     // use new windows coords as dimensions
         
   glMatrixMode(GL_MODELVIEW);    // set model transformation
   glLoadIdentity();              // to be empty (will talk about this later
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // ASCII value 27 = ESC key
	 exit(0);
}

// MousePress: Called when mouse is pressed.  Most likely the mouseMotion func will
// be called immediately afterwards if the mouse button is still down.
// NOTE: a single click will cause this function to be called twice
// once for GLUT_DOWN and once for GLUT_UP
void mousePress(GLint button, GLint state, GLint x, GLint y)
{
	if (button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
	 printf("LEFT Mouse Down\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  if (button==GLUT_LEFT_BUTTON  && state==GLUT_UP)
	{
	 printf("LEFT Mouse Up\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  
  if (button==GLUT_RIGHT_BUTTON  && state==GLUT_DOWN)
	{
	 printf("RIGHT Mouse Down\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  if (button==GLUT_RIGHT_BUTTON  && state==GLUT_UP)
	{
	 printf("RIGHT Mouse Up\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  
}              

// MouseMotion: Called anytime mouse moves and button _is_ pressed
// note that we don't know which button is pressed, so this works
// with left/right/middle button
// if we want to know which button, we need to set a global variable in the
// mousePress callback
void mouseMotion(int x, int y)
{
   mouseX = x;
	 mouseY = winH - y;
	 printf("Mouse motion (%i %i) with a button down \n", mouseX, mouseY); // we don't know which button!  Need a global to record it from mousePress() function
	 glutPostRedisplay();
} 

// call anytime mouse moves and no button presed
void mousePassiveMotion(int x, int y)
{ 
	 printf("Mouse motion (%i %i) _no_ button pressed \n", x, winH-y); // we don't know which button!  Need a global to record it from mousePress() function
}                       

void display()
{
    // Clear Color = black (you can change it)
	  // Clear the buffer
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(4.0);
    glBegin(GL_POINTS);
      glVertex2i(mouseX, mouseY);
    glEnd();
    
    glFlush();
    
    glutSwapBuffers(); 
     
}


// HEY, look, i'm ignoring the command line!
// 
int main(void)
{
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (512, 512);
   glutCreateWindow ("mouseMotion (lec3)");
   
   glutReshapeFunc (reshape);       // register respace (anytime window changes)
   glutKeyboardFunc (keyboard);     // register keyboard func
   glutMouseFunc (mousePress);      // register mouse press funct
   glutMotionFunc(mouseMotion);     // ** Note, the name is just glutMotionFunc (not glutMouseMotionFunc)
   glutPassiveMotionFunc(mousePassiveMotion); // Passive motion                 
   glutDisplayFunc (display);       // register display function
   glutMainLoop();
   
   return 1;

}
