#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<GL/glut.h>


GLfloat u[3] = { 0.0, 0.0, 1.0 };

GLfloat newMatrix[16];
GLfloat oldMatrix[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };
GLfloat quaternion[16] = { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };

int count = 0;
bool initiate = false;

// A cube
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },
{ 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, -1.0, 1.0 },
{ 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void polygon(int a, int b, int c, int d)
{

	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);

	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);

	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);

	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();

}

void colorcube(void)
{
	/* map vertices to faces */
	/* Faces of the cube     */
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}



void display(void)
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                  // M = I
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(quaternion);
	colorcube();
	glPopMatrix();
	glutSwapBuffers();                    // swap buffer
}



// SETUP KEYBOARD -- this program updates the square when the user presses ' '(space))
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(GLint button, GLint state, GLint tx, GLint ty)
{
	float cx = (tx - 250) / 250.0;
	float cy = (250 - ty) / 250.0;
	float d = cx*cx + cy*cy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		for (int i = 0; i < 16; i++){
			oldMatrix[i] = quaternion[i];
		}
		if (d > 1){
			u[0] = cx / sqrt(d);
			u[1] = cy / sqrt(d);
			u[2] = 0;
		}
		else{
			u[0] = cx;
			u[1] = cy;
			u[2] = sqrt(1 - d);
		}
	}
}

void mouseMotion(int x, int y)
{
	float cx, cy;
	cx = (x - 250) / 250.0;
	cy = (250 - y) / 250.0;

	GLfloat v[3];
	GLfloat n[3];
	GLfloat theta;
	float d = cx*cx + cy*cy;
	if (d > 1){
		v[0] = cx / sqrt(d);
		v[1] = cy / sqrt(d);
		v[2] = 0;
	}
	else{
		v[0] = cx;
		v[1] = cy;
		v[2] = sqrt(1 - d);
	}
	// obtain normal vector by u,v outer product
	n[0] = u[1] * v[2] - u[2] * v[1];
	n[1] = u[2] * v[0] - u[0] * v[2];
	n[2] = u[0] * v[1] - u[1] * v[0];
	float size_n = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

	// normalize the n vector
	n[0] /= size_n;
	n[1] /= size_n;
	n[2] /= size_n;
	theta = asin(size_n);
	//theta /= 30;

	float q[4];
	q[0] = cos(theta / 2);
	q[1] = n[0] * sin(theta / 2);
	q[2] = n[1] * sin(theta / 2);
	q[3] = n[2] * sin(theta / 2);


	// make custom matrix 
	newMatrix[0] = 1 - 2 * q[2] * q[2] - 2 * q[3] * q[3];
	newMatrix[1] = 2 * q[1] * q[2] + 2 * q[0] * q[3];
	newMatrix[2] = 2 * q[1] * q[3] - 2 * q[0] * q[2];
	newMatrix[4] = 2 * q[1] * q[2] - 2 * q[0] * q[3];
	newMatrix[5] = 1 - 2 * q[1] * q[1] - 2 * q[3] * q[3];
	newMatrix[6] = 2 * q[2] * q[3] + 2 * q[0] * q[1];
	newMatrix[8] = 2 * q[1] * q[3] + 2 * q[0] * q[2];
	newMatrix[9] = 2 * q[2] * q[3] - 2 * q[0] * q[1];
	newMatrix[10] = 1 - 2 * q[1] * q[1] - 2 * q[2] * q[2];

	quaternion[0] = oldMatrix[0] * newMatrix[0] + oldMatrix[1] * newMatrix[4] + oldMatrix[2] * newMatrix[8];
	quaternion[1] = oldMatrix[0] * newMatrix[1] + oldMatrix[1] * newMatrix[5] + oldMatrix[2] * newMatrix[9];
	quaternion[2] = oldMatrix[0] * newMatrix[2] + oldMatrix[1] * newMatrix[6] + oldMatrix[2] * newMatrix[10];
	quaternion[4] = oldMatrix[4] * newMatrix[0] + oldMatrix[5] * newMatrix[4] + oldMatrix[6] * newMatrix[8];
	quaternion[5] = oldMatrix[4] * newMatrix[1] + oldMatrix[5] * newMatrix[5] + oldMatrix[6] * newMatrix[9];
	quaternion[6] = oldMatrix[4] * newMatrix[2] + oldMatrix[5] * newMatrix[6] + oldMatrix[6] * newMatrix[10];
	quaternion[8] = oldMatrix[8] * newMatrix[0] + oldMatrix[9] * newMatrix[4] + oldMatrix[10] * newMatrix[8];
	quaternion[9] = oldMatrix[8] * newMatrix[1] + oldMatrix[9] * newMatrix[5] + oldMatrix[10] * newMatrix[9];
	quaternion[10] = oldMatrix[8] * newMatrix[2] + oldMatrix[9] * newMatrix[6] + oldMatrix[10] * newMatrix[10];

	display();

	
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
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("quaternion rotation");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

	glutMainLoop();
	return 	0;
}
