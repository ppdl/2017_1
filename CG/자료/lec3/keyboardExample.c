//  Example: keyboardExample.c
//

#include<stdlib.h>
#include<gl\glut.h>

int winW, winH;   // <---- window's width (W) and height (H)

int keyX=0, keyY=0; // <-- use globals to know the location of the mouse when the key was pressed

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

// called when a key is pressed 
void keyboard(unsigned char key, int x, int y)
{
    
	printf("Key \'%c\' (ASCII %i) pressed at location (%i %i) \n", key, (int)key, x, y);
	// the "(int) key" term above is called casting.  I have forced the key to be an integer
	
	if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
	 printf("   and CTRL button is down \n");
	
  keyX = x;
	keyY = winH - y;
	
	if (key == 27) // ASCII value 27 = ESC key
	{
	 exit(0);
  }
	
  glutPostRedisplay();
}              

                     

void display()
{
    // Clear Color = black (you can change it)
	  // Clear the buffer
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(4.0);
    glBegin(GL_POINTS);
      glVertex2i(keyX, keyY);
    glEnd();
    
    glFlush();
    
    glutSwapBuffers(); 
     
}


// HEY, look, i'm ignoring the command line!  Just put in (void)
// 
int main(void)
{
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (512, 512);
   glutCreateWindow ("keyboard Example (lec3)");
   
   glutReshapeFunc (reshape);       // register respace (anytime window changes)
   glutKeyboardFunc( keyboard );                 
   glutDisplayFunc (display);       // register display function
   glutMainLoop();
   
   return 1;

}
