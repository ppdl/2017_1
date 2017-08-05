//  Example: menExample2.c  (single menu callback)
//

#include<stdlib.h>
#include<gl\glut.h>


// Track
void reshape(int w, int h)
{
   
  glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
  glLoadIdentity();             // This clear any existing matrix
   
   gluOrtho2D (0, w, 0, h);     // use new windows coords as dimensions
         
   glMatrixMode(GL_MODELVIEW);    // set model transformation
   glLoadIdentity();              // to be empty (will talk about this later
}


void display()
{  
   glClearColor(0,1,1,0);
   glClear(GL_COLOR_BUFFER_BIT);
   
   glFlush();
  
}
// ONLY A SINGLE CALL BACK
void
menuCallback(int menuItem)
{
  printf(" menuItem = %i \n", menuItem);
  
  if (menuItem == 7)
    exit(0);
  
  glutPostRedisplay();
}

// 
int main(void)
{
   int rootMenu, subMenu1, subMenu2, subsubMenu1, subsubMenu2;        
   // variables to keep track of the menus
   
   glutInitDisplayMode (GLUT_RGB);
   glutInitWindowSize (512, 512);
   glutCreateWindow ("menuExample2 (lec3)");
          
   glutDisplayFunc (display);       // register display function
   
   // Register Menu CallBack
   rootMenu=glutCreateMenu(menuCallback);     // create root                  
   
   subMenu1=glutCreateMenu(menuCallback);     // create first subMenu
   subsubMenu1=glutCreateMenu(menuCallback);  
   glutAddMenuEntry("Big", 1);      // name and ID
   glutAddMenuEntry("Small", 2);    // name and ID
   subsubMenu2 = glutCreateMenu(menuCallback);
   glutAddMenuEntry("Red", 3);    // name and ID
   glutAddMenuEntry("Blue", 4);    // name and ID

   glutSetMenu(rootMenu);
   glutAddSubMenu("Rect", subMenu1);
   glutSetMenu(subMenu1);
   glutAddSubMenu("Size", subsubMenu1);
   glutAddSubMenu("Colour", subsubMenu2);
   
   subMenu2=glutCreateMenu(menuCallback);     // create first subMenu
   glutAddMenuEntry("Fast", 5);         // name and ID
   glutAddMenuEntry("Slow", 6);         // name and ID
   glutSetMenu(rootMenu);
   glutAddSubMenu("Speed", subMenu2);
   glutAddMenuEntry("Exit", 7);
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);            // Attach the menu to the RIGHT_BUTTON
  
  glutMainLoop();
   
  return 1;
}
