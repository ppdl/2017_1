/* ========================================================================== */
/*                                                                            */
/*   objectMaterials.c                                                               */
/*                                                                            */
/*   Description: Setup's materials for two different objects                                                            */
/*                                                                            */
/* ========================================================================== */


#include <GL/glut.h>

typedef struct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
  
} material;

int toggle=1;

/* advance C to initialize structs -- awesome, huh? */
material PolishedGold = {{0.24725, 0.2245, 0.0645, 1.0},
                         {0.34615, 0.3143, 0.0903, 1.0},
                         {0.797357, 0.723991, 0.208006, 1.0},  
                          83.2};
                          
material Pearl        = {{0.25, 0.20725, 0.20725, 0.922},
                         {1.0, 0.829, 0.829, 0.922},
                         {0.296648, 0.296648, 0.296648, 0.922},
                         11.264};


void init(void)
{
  /* 100% white light */
   GLfloat light_ambient[]={0.5, 0.5, 0.5, 1.0};
   GLfloat light_diffuse[]={0.5, 0.5, 0.5, 1.0};
   GLfloat light_specular[]={0.5, 0.5, 0.5,1.0};

   /* set up ambient, diffuse, and specular components for light 0 */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  
  /* set up ambient, diffuse, and specular components for light 1 */
  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    
   glClearColor (0.3, 0.3, 0.3, 1.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
}

void 
idle()
{
  glutPostRedisplay();
}

void setMaterial(material M)
{
    glMaterialfv(GL_FRONT, GL_SPECULAR, M.specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, M.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, M.diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, M.shininess);
}

void display()
{
    static float rot=0;
    static float rotL=0;
    static float position[4] = {0,2,0,1}; /* point light at (0,2,0) */
    static float position2[4] = {0, 0, 0, 1};
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Setup the view of the world */
    glMatrixMode(GL_PROJECTION);           // Switch to projection mode (P)
    glLoadIdentity();                      // P <- I

    gluPerspective( 60.0, 1.0, 1.0, 20); // P <- P
    
    glMatrixMode(GL_MODELVIEW);           // Switch to model view mode  (M)
    glLoadIdentity();                     // M = I
    
    gluLookAt( 0, 1, 4,   // M = RT(view)
               0, 0, 0, 
               0, 1, 0 );    
  
    /* Draw a sphere to represent the light-source */
      glDisable(GL_LIGHTING);   /* turn off lighting so I can use glColor */
      if (toggle)
		glColor3f(1,1,1);
      else
	    glColor3f(0,0,0);
    
	glPushMatrix();
    glTranslatef(0,1.5,0);
    glutSolidSphere(0.1,30,30);
    glPopMatrix();
    glEnable(GL_LIGHTING);  /* turn the lighting back on */
    
    glLightfv(GL_LIGHT0, GL_POSITION, position); /* set light defined above */
    

    //ROTATING LIGHT 
    glDisable(GL_LIGHTING);   // turn off lighting so I can use glColor 
    glColor3f(1,1,1);
    glPushMatrix();
     glRotatef(rotL, 0, 1, 0);
     glTranslatef(1.5, 1.5, 0);
     glutSolidSphere(0.1,30,30);
    glPopMatrix();
    glEnable(GL_LIGHTING);  // turn the lighting back on 

    /* Light rotated */
    glPushMatrix();
     glRotatef(rotL, 0, 1, 0);
    glTranslatef(1.5, 1.5, 0);
    glLightfv(GL_LIGHT1, GL_POSITION, position2); /* set light defined above */
    glPopMatrix();
    
    /* draw teapot one in Gold */
    setMaterial(PolishedGold);
    glPushMatrix();
    glTranslatef(1,0,0);
    glRotatef(rot,0,1,0);
    glutSolidTeapot(0.5);
    glPopMatrix();
    
   /* draw teapot one in Pearl */
    setMaterial(Pearl);
    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(rot,0,1,0);
    glutSolidTeapot(0.5);
    glPopMatrix();

    rot = rot + 0.5;
    rotL = rotL + 1;

  //  glFlush();
        
    glutSwapBuffers();
}

// SETUP KEYBOARD -- this program updates the square when the user presses ' '(space))
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:  /*  Escape Key  */
         exit(0);
         break;
      case ' ':
        if (toggle==1)
        {
          glDisable(GL_LIGHT0);
          toggle = 0;
        } 
        else
        {
          glEnable(GL_LIGHT0);
          toggle = 1;
        }
        break;
  }
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle); 
   glutMainLoop();
   return 0;
}