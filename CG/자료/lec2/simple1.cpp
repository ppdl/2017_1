	#include <GL/glut.h>

    // setup display function
	void mydisplay()
	{	
		glClear(GL_COLOR_BUFFER_BIT);   // clear the framebuffer


		glBegin(GL_POLYGON);  // start drawing a polygon

	    glVertex2f(-0.5, -0.5);       // v1     
        glVertex2f(-0.5, 0.5);        // v2      
        glVertex2f(0.5, 0.5);         // v3      
        glVertex2f(0.5, -0.5);        // v4     

		glEnd();  // end drawing polygon

		glFlush();  // This forces command to be displayed
	}

	int main(int argc, char** argv)
	{
		glutCreateWindow("simple1");  // <- Window name "simple1"  
		glutDisplayFunc(mydisplay);   // // <- GLUT Display Function is "mydisplay" 
		glutMainLoop();
	}