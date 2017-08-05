#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

#define TYPE_SPHERE 0
#define TYPE_CUBE 1
#define TYPE_CONE 2
#define TYPE_TORUS 3
#define TYPE_TEAPOT 4

#define MAX_OBJECT 110

#define LIGHT_WHITE 0
#define LIGHT_RED 1
#define LIGHT_GREEN 2
#define LIGHT_BLUE 3

GLfloat white_ambient[] = { 0.5, 0.5, 0.5, 0.8 };
GLfloat diffuse[] = { 0.5, 0.5, 0.5, 0.8 };
GLfloat specular[] = { 0.8, 0.8, 0.8, 1 };

GLfloat shinny[] = { 8 };
GLfloat zero[] = { 0, 0, 0, 1 };

class viewer
{
public:
	float x, y;
	float dirX, dirY;
	float theta;
};

class objt
{
public:
	int type;
	float x, y;
	float r, g, b;
	float theta;

	void draw()
	{
		glPushMatrix();
		GLfloat mat_ambient[] = { r, g, b, 0.6 };
		GLfloat mat_specular[] = { r*1.3, g*1.3, b*1.3, 1 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, zero);
		glMaterialfv(GL_FRONT, GL_SHININESS, shinny);
		switch (type)
		{
		case TYPE_CONE:
			glTranslatef(x, y, 0);
			glutSolidCone(3.7, 7, 20, 20);
			break;
		case TYPE_SPHERE:
			glTranslatef(x, y, 4.7);
			glutSolidSphere(4.7, 30, 30);
			break;
		case TYPE_CUBE:
			glTranslatef(x, y, 3.0);
			glRotatef(theta, 0, 0, 1);
			glutSolidCube(6);
			break;
		case TYPE_TORUS:
			glTranslatef(x, y, 5.2);
			glRotatef(theta, 0, 0, 1);
			glRotatef(90, 1.0, 0, 0);
			glutSolidTorus(1.3, 4.0, 40, 40);
			break;
		case TYPE_TEAPOT:
			glTranslatef(x, y, 2.7);
			glRotatef(theta, 0, 0, 1);
			glRotatef(90, 1.0, 0, 0);
			glutSolidTeapot(4);
		}
		glPopMatrix();
	}

	float GetDist(int x1, int y1)
	{
		return sqrtf((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y));
	}
};

int winW, winH;
viewer V;
bool birdView = false;
objt obj[MAX_OBJECT];
float light_x = 0, light_y = 0;
bool pointlight = true;
int light_dir = 0;
GLfloat dir_light[4][4] = { { 2, 0, 1, 0 }, { 0, 2, 1, 0 }, { -2, 0, 1, 0 }, { 0, -2, 1, 0 } };
int sel_idx;
bool isSel = false;

void lightning()
{
	glPushMatrix();
	if (pointlight)
	{
		GLfloat light_pos[] = { light_x, light_y, 19, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	}
	else
	{
		glLightfv(GL_LIGHT0, GL_POSITION, dir_light[light_dir]);
	}
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (birdView)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-210, 210, -210, 210, 10, 250);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 220, 0, 0, 0, 0, 1, 0);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 1.0, 3.0, 800);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(V.x, V.y, 5.0, V.x + V.dirX, V.y + V.dirY, 5.0, 0.0, 0.0, 1.0);
	}

	//draw
	glDisable(GL_LIGHTING);
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex3f(200.0, 200.0, 0.0);
	glVertex3f(-200.0, 200.0, 0.0);
	glVertex3f(-200.0, -200.0, 0.0);
	glVertex3f(200.0, -200.0, 0.0);
	glEnd();

	if (birdView)
	{
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(V.x, V.y, 8);
		glRotatef(V.theta*180.0 / 3.141592, 0, 0, 1.0);
		glRotatef(90, 1.0, 0, 0);
		glutSolidTeapot(5);
		glPopMatrix();
	}
	if (pointlight)
	{
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(light_x, light_y, 20);
		glutSolidSphere(3, 15, 15);
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	lightning();

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		obj[i].theta += 1.5;
		if (obj[i].theta > 360) obj[i].theta = 0;
		obj[i].draw();
	}

	glutSwapBuffers();
}

void init()
{
	V.x = 0.0, V.y = 0.0;
	V.dirX = 1.0, V.dirY = 0;
	V.theta = 0.0;
	srand(time(NULL));
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		obj[i].r = (float)(rand() % 1001) / 1000.0;
		obj[i].g = (float)(rand() % 1001) / 1000.0;
		obj[i].b = (float)(rand() % 1001) / 1000.0;
		obj[i].type = rand() % 5;
		obj[i].x = (rand() % 391) - 195;
		obj[i].y = (rand() % 391) - 195;
		obj[i].theta = (float)(rand() % 360);
	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

}

void timer(int n)
{
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);
	else if (key == ' ')
		birdView = (birdView == false) ? true : false;
	else if (key == 'a' || key == 'A')
	{
		V.theta += 0.07;
		if (V.theta >= 6.28) V.theta -= 6.28;
		V.dirX = cosf(V.theta);
		V.dirY = sinf(V.theta);
	}
	else if (key == 'd' || key == 'D')
	{
		V.theta -= 0.07;
		if (V.theta <= 0.0) V.theta += 6.28;
		V.dirX = cosf(V.theta);
		V.dirY = sinf(V.theta);
	}
	else if (key == 'w' || key == 'W')
	{
		V.x += V.dirX * 2.5;
		V.y += V.dirY * 2.5;
		if (V.x > 197) V.x = 197;
		else if (V.x < -197) V.x = -197;
		if (V.y > 197) V.y = 197;
		else if (V.y < -197) V.y = -197;
	}
	else if (key == 's' || key == 'S')
	{
		V.x -= V.dirX * 2.5;
		V.y -= V.dirY * 2.5;
		if (V.x > 197) V.x = 197;
		else if (V.x < -197) V.x = -197;
		if (V.y > 197) V.y = 197;
		else if (V.y < -197) V.y = -197;
	}
	else if (key == 'q' || key == 'Q')
	{
		V.x -= V.dirY * 2.2;
		V.y += V.dirX * 2.2;
		if (V.x > 197) V.x = 197;
		else if (V.x < -197) V.x = -197;
		if (V.y > 197) V.y = 197;
		else if (V.y < -197) V.y = -197;
	}
	else if (key == 'e' || key == 'E')
	{
		V.x += V.dirY * 2.2;
		V.y -= V.dirX * 2.2;
		if (V.x > 197) V.x = 197;
		else if (V.x < -197) V.x = -197;
		if (V.y > 197) V.y = 197;
		else if (V.y < -197) V.y = -197;
	}
	else if (key == '\'')
	{
		pointlight = !pointlight;
	}
	else if (key == ';')
	{
		light_dir = (light_dir + 1) % 4;
	}
	else if (key == 'n' || key == 'N')
	{
		srand(time(NULL));
		for (int i = 0; i < MAX_OBJECT; i++)
		{
			obj[i].r = (float)(rand() % 1001) / 1000.0;
			obj[i].g = (float)(rand() % 1001) / 1000.0;
			obj[i].b = (float)(rand() % 1001) / 1000.0;
			obj[i].type = rand() % 5;
			obj[i].x = (rand() % 391) - 195;
			obj[i].y = (rand() % 391) - 195;
			obj[i].theta = (float)(rand() % 360);
		}
	}
}

void skeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		light_x = (light_x <= -205) ? -205 : light_x - 3.5;
		break;
	case GLUT_KEY_RIGHT:
		light_x = (light_x >= 205) ? 205 : light_x + 3.5;
		break;
	case GLUT_KEY_UP:
		light_y = (light_y >= 205) ? 205 : light_y + 3.5;
		break;
	case GLUT_KEY_DOWN:
		light_y = (light_y <= -205) ? -205 : light_y - 3.5;
		break;
	}
}

void mouse(GLint button, GLint state, GLint tx, GLint ty)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (birdView == true)
		{
			int x = tx * 420 / winW - 210;
			int y = 210 - ty * 420 / winH;

			sel_idx = -1;
			float min = 1000;
			float temp;
			for (int i = 0; i < MAX_OBJECT; i++)
			{
				temp = obj[i].GetDist(x, y);
				if (temp <= 5.0 && temp <= min)
				{
					min = temp;
					sel_idx = i;
					isSel = true;
				}
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isSel = false;
	}
}

void motion(int tx, int ty)
{
	if (isSel && birdView)
	{
		int x = tx * 420 / winW - 210;
		int y = 210 - ty * 420 / winH;

		obj[sel_idx].x = x;
		obj[sel_idx].y = y;
	}
}


int main()
{
	winW = 700, winH = 700;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("3d world!");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(skeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(33, timer, 0);
	glutMainLoop();
}