/* 3D Gasket (from book) */
#include <GL/glut.h>

/* GLOBAL VARIABLES */
/* initial tetrahedron */
GLfloat v[4][3] = { { 0.0, 0.0, 1.0 },
{ 0.0, 0.942809, -0.33333 },
{ -0.816497, -0.471405, -0.333333 },
{ 0.816497, -0.471405, -0.333333 } };

int n;

void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
/* display one triangle */
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{

	GLfloat v1[3], v2[3], v3[3];
	int j;
	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j<3; j++) v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j<3; j++) v3[j] = (b[j] + c[j]) / 2;
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
	}
	else(triangle(a, b, c)); /* draw triangle at end of recursion */
}

void tetrahedron(int m)
{
	/* Apply triangle subdivision to faces of tetrahedron */

	glColor3f(1.0, 0.0, 0.0);
	divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0.0, 1.0, 0.0);
	divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[0], v[3], v[1], m);
	glColor3f(0.0, 0.0, 0.0);
	divide_triangle(v[0], v[2], v[3], m);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // <- added to clear the z-buffer
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	tetrahedron(n);
	glEnd();
	glFlush();
}

void init()
{
	glEnable(GL_DEPTH_TEST);    // enable depth testing (i.e. z-buffer))
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

// main function
void
main(int argc, char **argv)
{
	n = 4;                                          // levels of recursion
	glutInit(&argc, argv);                        // can ignore this
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  // <- add depth buffer (z buffer)
	glutInitWindowSize(500, 500);                 // window size
	glutCreateWindow("3D Gasket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);

	init();  // Its back!

	glutMainLoop();
}
