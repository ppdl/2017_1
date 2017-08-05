// -----------------------------------------
// Simple3.c
// 
// A slightly more complicated version that doesn't rely on defaults.
//

// include glut.h -- you'll need to have installed glut,
// see course notes/webpage
#include <GL/glut.h>

// declares a function "init" used to initialize application variables,
// openGL state
void init()
{
    glClearColor (0.0, 0.0, 0.0, 1.0);// sets background color to (0,0,0)=black
    glColor3f(1.0, 1.0, 1.0);         // sets forground color to (1,1,1)=white
       
    glViewport(500,500,0,0);
    glMatrixMode (GL_PROJECTION);     // sets up "projection" matrix   
    glLoadIdentity ();                // this clears the current matrix (if any)
   
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);   // volume is
                                                // a 2x2x2 centered at (0,0,0)

    // call's paramters glOrtho(left,right,bottom,top,zNear,zFar)                                             
}


// setup display function
void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the framebuffer
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);              // start drawing a polygon 
        glColor3ub(255,0,0);          // Red  
        glVertex2f(-0.5, -0.5);       
        glColor3ub(0, 255,0);         // Green
        glVertex2f(-0.5, 0.5);      
        glColor3ub(0,0,255);          // Blue  
        glVertex2f(0.5, 0.5);         
        glColor3ub(255,255,255);      // White
        glVertex2f(0.5, -0.5);        
        
    glEnd();                          // end drawing polygon
    
    glFlush();                        // This forces command to be displayed
                                     
                                      
  // NOTE: glColor3ub, you could also us glColor3f(1, 0, 0)
     
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);                        // not really necessary, but a good habit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // this means single buffer, RGB color     
	glutInitWindowSize(500,500);    	           // window size
	glutInitWindowPosition(0,0);                 // requested position
	glutCreateWindow("simple");                  // create the window (with name)
	glutDisplayFunc(mydisplay);                  // register display function callback
  
	init();                                      // initialize variables
   
	glutMainLoop();                              // call main loop
}

                                 