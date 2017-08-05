//  Example: BoxDrop1.c


// standard, get use to putting this in.
#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
	// setup that we want anti-aliasing lines (talk about this later in class)
	// set line width to 1
	glClearColor(0,0,0,1.0);
	glColor3f(1,1,1);

   
   // call reshape() to setup the viewing coordinates!  
   // This is a cheap way to reuse code, otherwise you could put all of that
   // code here.
}


// Setup the viewing transform
// This setup up a display with coordiantes x axis -50 to 50, y axis -50 to 50 
// This callback is called anytime the window size changes (for example, you resize)
// in Windows
void reshape(int w, int h)
{
   glViewport(0, 0, w, h);       // maps to window 0,0, with * height
   glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
   glLoadIdentity();             // This clear any existing matrix
   
   
    // This is a common approach in OpenGL  -- the world does is always the same, no matter
    // the window dim.  So, we need to normalize in case the width and height 
   if (w <= h)                    // normalize by which dimensin is longer 
      gluOrtho2D (-50.0, 50.0, 
         -50.0*(GLfloat)h/(GLfloat)w, 50.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (-50.0*(GLfloat)w/(GLfloat)h, 
         50.0*(GLfloat)w/(GLfloat)h, -50.0, 50.0);
  

   glMatrixMode(GL_MODELVIEW);    // set model transformation
   glLoadIdentity();              // to be empty (will talk about this later
}

// Draw a square about the origin
void drawBox(double y_offset)
{
  glBegin(GL_LINE_LOOP);               
    glVertex2f(1.0, 1.0+y_offset);    // v1    v4 --> v1
    glVertex2f(1.0, -1.0+y_offset);   // v2    ^      |
    glVertex2f(-1.0,-1.0+y_offset);   // v3    |      v  
    glVertex2f(-1.0, 1.0+y_offset);   // v4   v3 ---  v2
  glEnd();
  
  glFlush();
}

/* Display Function */
void display(void)
{
    static double y_offset = 50;  // "static" means global variable in C, scoped by the function
                                  // you could have declared this as a global, also Ok                   

	 // Clear Color = black
	 // Clear the buffer
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT); 
  
    drawBox(y_offset);     // Draw with offset
    
    y_offset-=1.0;        //  Advance offset
    if (y_offset < -50)
      y_offset = 50;

    glutSwapBuffers();   // Using double-buffer, swap the buffer to display
}
 

// SETUP KEYBOARD -- this program updates the square when the user presses ' '(space))
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
		case ' ':    /* Call display function */
         glutPostRedisplay();	
         break;
      case 27:  /*  Escape Key  */
         exit(0);
         break;
      default:
         break;
    }
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGB display mode, and handle input events.
 *
 *  We have registered a keyboard function.  The animation of the
 *  square is updated each time you press ' '.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);   // not necessary unless on Unix
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (512, 512);
   glutCreateWindow (argv[0]);
   init();
   
   glutReshapeFunc (reshape);       // register reshape (anytime window changes)
   glutKeyboardFunc (keyboard);     // register keyboard (anytime keypressed)                                        
   glutDisplayFunc (display);       // register display function
   glutMainLoop();
//   return 0;
}
