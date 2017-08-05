//  Example: windowTrack.c
//

#include<stdlib.h>
#include<gl\glut.h>

int winW, winH;   // <---- window's width (W) and height (H)

int mouseX=0, mouseY=0; // <-- use globals to know last mouse click location

// Track
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

void mousePress(GLint button, GLint state, GLint x, GLint y)
{
	if (button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
	 printf("Mouse Down\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  if (button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
	 printf("Mouse Up\n");
	 mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
  }
  
  if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
  {
    exit(0);
  }
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
   glutCreateWindow ("windowTrack (lec3)");
   
   glutReshapeFunc (reshape);       // register respace (anytime window changes)
   glutMouseFunc (mousePress);      // register mouse                             
   glutDisplayFunc (display);       // register display function
   glutMainLoop();
   
   return 1;

}
