/*  CODE - from Angle book */
/* recursive subdivision of triangle to form Sierpinski gasket */
/* number of recursive steps given on command line */

#include <GL/glut.h>

/* initial 2D triangle */
GLfloat v[3][2]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};  // try making the triangle bigger

int n;                   // global variable to control levels of sub-division

/* Draw one triangle */
void triangle( GLfloat *a, GLfloat *b, GLfloat *c)
{
       glVertex2fv(a);
       glVertex2fv(b);
       glVertex2fv(c);
}

void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
/* triangle subdivision using vertex numbers */

    GLfloat v0[2], v1[2], v2[2];
    int j;
    if(m>0)
    {
        for(j=0; j<2; j++) v0[j]=(a[j]+b[j])/2;
        for(j=0; j<2; j++) v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++) v2[j]=(b[j]+c[j])/2;
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else triangle(a,b,c); /* draw triangle at end of recursion */
}


// draw 2D triangle
void display()
{
    glEnable (GL_LINE_SMOOTH);                // add this line!
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);    
    divide_triangle(v[0], v[1], v[2], n);     // call function here -- with stop n
    glEnd();
    glFlush();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);        // setup projection
    glLoadIdentity();                   // identity
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);   // volume is -2, 2 by -2, 2 [z is assumed 0]
    glMatrixMode(GL_MODELVIEW);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0,0.0,0.0);
}

int main(int argc, char **argv)
{
    n=5;                                        // set stop n=5
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(display);                 // register display
    
    myinit();                                 // init
    
    glutMainLoop();                           // enter main loop
                                              // notice, no retun -- compiler may give an error
}
