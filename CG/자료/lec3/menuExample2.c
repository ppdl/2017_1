//  Example: menExample2.c  (single menu callback)
//

#include<stdlib.h>
#include<gl\glut.h>

int winW, winH;   // <---- window's width (W) and height (H)

int mouseX=0, mouseY=0; // <-- use globals to know last mouse click location

/* The user needs to assign an ID to each menu entry
   This is up to the user, there is no rule how to do this.
   Here I have just defined constants for each menu item */
#define MenuItemBig       1
#define MenuItemSmall     2
#define SubMenuColorRed   3
#define SubMenuColorBlue  4
#define MenuItemExit      5

int DrawBig=1;    // If Big=0 then draw smale, else big
int DrawRed=1;    // If Red=0 then draw blue, else red

// Track
void 
reshape(int w, int h)
{
  winW = w;
  winH = h;
   
  glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
  glLoadIdentity();             // This clear any existing matrix
   
   gluOrtho2D (0, w, 0, h);     // use new windows coords as dimensions
         
   glMatrixMode(GL_MODELVIEW);    // set model transformation
   glLoadIdentity();              // to be empty (will talk about this later
}

// called when mouse is first pressed.  Most likely the mouseMotion func will
// be called immediately afterwards if the mouse button is still down.
// NOTE: a single click will cause this function to be called twice
// once for GLUT_DOWN and once for GLUT_UP
void 
mousePress(GLint button, GLint state, GLint x, GLint y)
{
	if (button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
	 mouseX = x;
	 mouseY = winH - y;
	 printf("Left button pressed\n");
	 glutPostRedisplay();
  }
  
  if (button==GLUT_RIGHT_BUTTON)
  {
    // This will never be called since menu is attached to right button
    printf(" RIGHT BUTTON PRESSED \n");
  }
}              

// called anytime mouse moves and button _is_ pressed
// note that we don't know which button is pressed, so this works
// with left/right/middle button
// if we want to know which button, we need to set a global variable in the
// mousePress callback
void 
mouseMotion(int x, int y)
{
   mouseX = x;
	 mouseY = winH - y;
	 glutPostRedisplay();
}                     

void display()
{
    // Clear Color = black (you can change it)
	  // Clear the buffer
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (DrawBig)
      glPointSize(8.0);
    else
      glPointSize(2.0);
      
    if (DrawRed)
      glColor3ub(255,0,0);
    else
      glColor3ub(0,0,255);
      
    glBegin(GL_POINTS);
      glVertex2i(mouseX, mouseY);
    glEnd();
    
    glFlush();
    
    glutSwapBuffers(); 
     
}
// ONLY A SINGLE CALL BACK
void
menuCallback(int menuItem)
{
  switch (menuItem)
  { 
    case MenuItemBig    : DrawBig = 1;  break;
    case MenuItemSmall  : DrawBig = 0;  break;
    case MenuItemExit   : exit(0);      break;
    case SubMenuColorRed   : DrawRed = 1;  break;
    case SubMenuColorBlue  : DrawRed = 0;  break;
  }
  
  glutPostRedisplay();
}

// 
int main(void)
{
   int rootMenu, subMenu;         // variables to keep track of the menus
   
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (512, 512);
   glutCreateWindow ("menuExample2 (lec3)");
   
   glutReshapeFunc (reshape);       // register respace (anytime window changes)
   glutMotionFunc  (mouseMotion);
   glutMouseFunc   (mousePress);          
   glutDisplayFunc (display);       // register display function
   
   // Register Menu CallBack
   rootMenu=glutCreateMenu(menuCallback);                    // func to call at root menu level
   // Create menu items at root level
   glutAddMenuEntry("Big Point", MenuItemBig);      // name and ID
   glutAddMenuEntry("Small Point", MenuItemSmall);  // name and ID
    
  // Create a sub menu -- it won't appear until we add it
  subMenu=glutCreateMenu(menuCallback);      // Each sub menu can have a call back
  glutAddMenuEntry("(Red)",SubMenuColorRed);    // these entries are automatically under the sub-menu since it was the last created menu
  glutAddMenuEntry("(Blue)",SubMenuColorBlue);  
  
  glutSetMenu(rootMenu);                        // Switch back to root menu
  glutAddSubMenu("Point Colour",subMenu);       // Add the menu to the root
  glutAddMenuEntry("Exit",MenuItemExit);        // Add an exit item      
   
  glutAttachMenu(GLUT_RIGHT_BUTTON);            // Attach the menu to the RIGHT_BUTTON
  
  glutMainLoop();
   
  return 1;

}
